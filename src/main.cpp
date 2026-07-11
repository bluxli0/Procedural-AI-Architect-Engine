#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/utils/cocos.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace geode::prelude;

// ==========================================
// 🌍 GLOBAL EDITOR HANDLE
// ==========================================
static LevelEditorLayer* g_omniEditor = nullptr;

// ==========================================
// 🎨 TYPES, CONSTANTS & CONFIGURATION ENUMS
// ==========================================
struct ColorHarmony {
    cocos2d::ccColor3B primary;
    cocos2d::ccColor3B secondary;
    cocos2d::ccColor3B accent;
};

enum EffectStyle { CLASSIC_GLOW = 0, THUNDER_STORM = 1, MAGIC_GLOW = 2, MYTHIC_PORTAL = 3 };
enum DrawBrush   { SOLID_BLOCK = 0, DECORATION_LINE = 1, SPIKE_CHAIN = 2, GRADIENT_3D_ILLUSION = 3 };
enum EndTheme    { CINEMATIC_SLOMO = 0, TEXT_CREDIT_REEL = 1, QUANTUM_SINGULARITY = 2 };

// ==========================================
// 🧠 CO-CREATOR MASTER OMNI-ENGINE CORE
// ==========================================
class ProArchitectEngine {
public:
    static ColorHarmony generateHarmonicPalette(float baseHue) {
        auto hsvToRgb = [](float h, float s, float v) -> cocos2d::ccColor3B {
            h = fmod(h, 360.0f); if (h < 0.0f) h += 360.0f;
            float c = v * s;
            float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
            float m = v - c;
            float r = 0, g = 0, b = 0;
            if (h < 60) { r = c; g = x; }
            else if (h < 120) { r = x; g = c; }
            else if (h < 180) { g = c; b = x; }
            else if (h < 240) { g = x; b = c; }
            else if (h < 300) { r = x; b = c; }
            else { r = c; b = x; }
            return { static_cast<GLubyte>((r + m) * 255), static_cast<GLubyte>((g + m) * 255), static_cast<GLubyte>((b + m) * 255) };
        };
        return { hsvToRgb(baseHue, 0.85f, 0.9f), hsvToRgb(baseHue + 120.0f, 0.75f, 0.8f), hsvToRgb(baseHue + 240.0f, 0.95f, 0.95f) };
    }

    static void injectEffectSystem(LevelEditorLayer* editor, float x, float y, EffectStyle style) {
        if (!editor) return;
        int ids[] = {221, 2397, 2391, 8520};
        editor->createObject(ids[style], {x, y}, true);
    }

    static void buildIsometric3DShape(LevelEditorLayer* editor, float startX, float startY, int slices) {
        if (!editor) return;
        for (int i = 0; i < slices; i++) {
            float scale = 1.0f - (i * 0.15f);
            auto slice = editor->createObject(1, {startX + (i * 6.0f), startY + (i * 6.0f)}, true);
            if (slice) { slice->setScale(scale); slice->setZOrder(i); }
        }
    }

    static void buildDynamicEndScreen(LevelEditorLayer* editor, float x, float y, EndTheme theme) {
        if (!editor) return;
        editor->createObject(1979, {x, y}, true);
        int ids[] = {1915, 3910, 8505};
        editor->createObject(ids[theme], {x + 50, y}, true);
    }
};

// ==========================================
// 🎨 INTEGRATED MASTER INTERACTION PANEL
// ==========================================
class ProArchitectUIDock : public FLAlertLayer {
    LevelEditorLayer* m_editor;
    int m_brush = 0, m_fx = 0, m_end = 0;
    float m_hue = 180.0f;

public:
    static ProArchitectUIDock* create(LevelEditorLayer* editor) {
        auto ret = new ProArchitectUIDock();
        if (ret && ret->init(editor)) { ret->autorelease(); return ret; }
        CC_SAFE_DELETE(ret); return nullptr;
    }

    bool init(LevelEditorLayer* editor) {
        if (!FLAlertLayer::init(150)) return false;
        m_editor = editor;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        m_mainLayer = CCLayer::create();
        this->addChild(m_mainLayer);

        auto bg = CCScale9Sprite::create("GJ_square01.png");
        bg->setContentSize({380, 320});
        bg->setPosition(winSize / 2);
        m_mainLayer->addChild(bg);

        m_buttonMenu = CCMenu::create();
        m_mainLayer->addChild(m_buttonMenu);

        auto closeBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, menu_selector(ProArchitectUIDock::onClose));
        closeBtn->setPosition({-175, 145});
        m_buttonMenu->addChild(closeBtn);

        auto title = CCLabelBMFont::create("OMNI ARCHITECT PRO", "goldFont.fnt");
        title->setPosition(winSize.width / 2, winSize.height / 2 + 135);
        m_mainLayer->addChild(title);

        // UI BUTTONS
        auto genBtn = CCMenuItemSpriteExtra::create(ButtonSprite::create("GENERATE", "goldFont.fnt", "GJ_button_01.png", 0.7f), this, menu_selector(ProArchitectUIDock::onRun));
        genBtn->setPosition({0, -115});
        m_buttonMenu->addChild(genBtn);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        return true;
    }

    void onBrushChange(CCObject* s) { m_brush = s->getTag(); }
    void onClose(CCObject*) { this->removeFromParentAndCleanup(true); }
    void onRun(CCObject*) {
        ProArchitectEngine::injectEffectSystem(m_editor, 500, 150, (EffectStyle)m_fx);
        Notification::create("Build Complete!", NotificationIcon::Success)->show();
        onClose(nullptr);
    }
};

// ==========================================
// 🟡 DRAGGABLE FLOATING AI BUTTON (MODERN)
// ==========================================
class OmniDragButton : public CCMenuItemSpriteExtra {
    CCPoint m_lastPos;
    bool m_isDragging = false;

public:
    static OmniDragButton* create() {
        auto spr = ButtonSprite::create("AI", "goldFont.fnt", "GJ_button_01.png", 0.8f);
        auto ret = new OmniDragButton();
        if (ret && ret->init(spr, nullptr, nullptr)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret); return nullptr;
    }

    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event) override {
        m_lastPos = touch->getLocation();
        m_isDragging = false;
        return CCMenuItemSpriteExtra::ccTouchBegan(touch, event);
    }

    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event) override {
        CCMenuItemSpriteExtra::ccTouchMoved(touch, event);
        auto pos = touch->getLocation();
        if (pos.getDistance(m_lastPos) > 10.0f) m_isDragging = true;
        
        if (m_isDragging) {
            this->getParent()->setPosition(this->getParent()->getPosition() + (pos - m_lastPos));
            m_lastPos = pos;
        }
    }

    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event) override {
        if (!m_isDragging) {
            if (g_omniEditor) ProArchitectUIDock::create(g_omniEditor)->show();
            else Notification::create("Editor Null!", NotificationIcon::Error)->show();
        }
        CCMenuItemSpriteExtra::ccTouchEnded(touch, event);
        m_isDragging = false;
    }
};

// ==========================================
// 🧩 GAME HOOKS (THE INJECTION)
// ==========================================
class $modify(OmniLEL, LevelEditorLayer) {
    bool init(GJGameLevel* l, bool p1) {
        if (!LevelEditorLayer::init(l, p1)) return false;
        g_omniEditor = this;
        return true;
    }
};

class $modify(OmniUI, EditorUI) {
    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;
        g_omniEditor = lel;

        auto winSize = CCDirector::get()->getWinSize();
        auto menu = CCMenu::create();
        menu->setPosition({winSize.width / 2, winSize.height - 40});
        menu->setID("omni-float-menu");
        
        auto dragBtn = OmniDragButton::create();
        menu->addChild(dragBtn);
        this->addChild(menu, 9999);

        return true;
    }
};
