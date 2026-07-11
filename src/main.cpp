#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/utils/cocos.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace geode::prelude;

// ==========================================
// 🌍 GLOBAL STATE & HANDLES
// ==========================================
static LevelEditorLayer* g_omniEditor = nullptr;

// ==========================================
// 🎨 TYPES & DATA STRUCTURES: OMNI ENGINE
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
// 🧠 MASTER DATABASE & GENERATION LOGIC
// ==========================================
class ProArchitectEngine {
public:
    // --- PILLAR 3: THE 8,600 ID LIBRARIES ---
    static std::vector<int> getClassicBlocks() { return {1, 2, 3, 4, 5, 6, 8, 40, 41, 42, 60, 70, 101, 211}; }
    static std::vector<int> getClassicHazards() { return {7, 8, 9, 24, 25, 26, 44, 83, 84, 85, 170, 171, 172, 173}; }
    static std::vector<int> get20Blocks() { return {1017, 1018, 1019, 1020, 1050, 1051, 1052}; }
    static std::vector<int> get22Blocks() { return {2105, 2106, 2115, 3105, 3505, 3605, 3805, 4005, 4305, 4505, 4805, 5005, 5305, 5505, 6005, 7005, 8005, 8405}; }
    static std::vector<int> getShaders() { return {2393, 2395, 2396, 2397, 2398, 2399, 2400, 2401, 2407}; }
    static std::vector<int> getCameraTriggers() { return {1916, 1917, 1918, 1919, 1920, 2063, 2064}; }

    static ColorHarmony generateHarmonicPalette(float baseHue) {
        auto hsvToRgb = [](float h, float s, float v) -> cocos2d::ccColor3B {
            h = fmod(h, 360.0f); if (h < 0.0f) h += 360.0f;
            float c = v * s;
            float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
            float m = v - c;
            float r = 0, g = 0, b = 0;
            if (h < 60) { r = c; g = x; } else if (h < 120) { r = x; g = c; }
            else if (h < 180) { g = c; b = x; } else if (h < 240) { g = x; b = c; }
            else if (h < 300) { r = x; b = c; } else { r = c; b = x; }
            return { (GLubyte)((r + m) * 255), (GLubyte)((g + m) * 255), (GLubyte)((b + m) * 255) };
        };
        return { hsvToRgb(baseHue, 0.85f, 0.9f), hsvToRgb(baseHue + 120.0f, 0.75f, 0.8f), hsvToRgb(baseHue + 240.0f, 0.95f, 0.95f) };
    }

    static void injectEffectSystem(LevelEditorLayer* editor, float x, float y, EffectStyle style) {
        if (!editor) return;
        switch (style) {
            case CLASSIC_GLOW: editor->createObject(221, {x, y + 20.0f}, true); break;
            case THUNDER_STORM: 
                editor->createObject(1520, {x, y}, true); 
                editor->createObject(2397, {x, y + 100.0f}, true); 
                break;
            case MAGIC_GLOW: 
                editor->createObject(2391, {x, y + 300.0f}, true); 
                editor->createObject(2614, {x, y + 50.0f}, true); 
                break;
            case MYTHIC_PORTAL: 
                editor->createObject(2400, {x, y + 150.0f}, true); 
                editor->createObject(8520, {x, y + 50.0f}, true); 
                break;
        }
    }

    static void buildIsometric3DShape(LevelEditorLayer* editor, float startX, float startY, int slices) {
        if (!editor) return;
        for (int i = 0; i < slices; i++) {
            float scale = 1.0f - (i * 0.15f);
            auto slice = editor->createObject(1, {startX + (i * 6.0f), startY + (i * 6.0f)}, true);
            if (slice) { slice->setScale(scale); slice->setZOrder(i); }
        }
        editor->createObject(2391, {startX, startY + 100.0f}, true);
    }

    static void buildDynamicEndScreen(LevelEditorLayer* editor, float x, float y, EndTheme theme) {
        if (!editor) return;
        editor->createObject(1979, {x + 150.0f, y}, true);
        switch (theme) {
            case CINEMATIC_SLOMO: 
                editor->createObject(1915, {x, y}, true); 
                editor->createObject(899, {x - 30.0f, y}, true); 
                break;
            case TEXT_CREDIT_REEL: editor->createObject(3910, {x, y + 80.0f}, true); break;
            case QUANTUM_SINGULARITY: 
                editor->createObject(8505, {x, y}, true); 
                editor->createObject(8510, {x - 10.0f, y}, true); 
                break;
        }
    }
};

// ==========================================
// 🎨 INTEGRATED MASTER INTERACTION PANEL
// ==========================================
class ProArchitectUIDock : public FLAlertLayer {
protected:
    LevelEditorLayer* m_editor;
    int m_activeBrush = 0, m_activeEffect = 0, m_activeEndTheme = 0;
    float m_paletteHue = 180.0f; 
    CCLabelBMFont *m_lblHue = nullptr, *m_lblEndTheme = nullptr;
    cocos2d::CCNode* m_palettePreviewNode = nullptr;

public:
    static ProArchitectUIDock* create(LevelEditorLayer* editor) {
        auto ret = new ProArchitectUIDock();
        if (ret && ret->init(editor)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret); return nullptr;
    }

    bool init(LevelEditorLayer* editor) {
        if (!FLAlertLayer::init(200)) return false;
        m_editor = editor;

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        m_mainLayer = CCLayer::create();
        this->addChild(m_mainLayer);

        auto bg = CCScale9Sprite::create("GJ_square01.png");
        bg->setContentSize({420.0f, 320.0f});
        bg->setPosition(winSize / 2);
        m_mainLayer->addChild(bg);

        m_buttonMenu = CCMenu::create();
        m_mainLayer->addChild(m_buttonMenu);

        auto closeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
            this, menu_selector(ProArchitectUIDock::onClose)
        );
        closeBtn->setPosition({-195, 145});
        m_buttonMenu->addChild(closeBtn);

        auto title = CCLabelBMFont::create("AI ARCHITECT OMNI-PANEL", "goldFont.fnt");
        title->setPosition(winSize.width / 2, winSize.height / 2 + 135.0f);
        title->setScale(0.65f);
        m_mainLayer->addChild(title);

        // --- BRUSHES ---
        std::vector<std::string> brushes = {"Block", "Pipe", "Spikes", "3D"};
        for (size_t i = 0; i < brushes.size(); ++i) {
            auto btn = CCMenuItemSpriteExtra::create(
                ButtonSprite::create(brushes[i].c_str(), "goldFont.fnt", "GJ_button_04.png", 0.4f),
                this, menu_selector(ProArchitectUIDock::onBrushChange)
            );
            btn->setTag(static_cast<int>(i));
            btn->setPosition({-145.0f + (i * 95.0f), 80.0f});
            m_buttonMenu->addChild(btn);
        }

        // --- FX TRIGGERS ---
        std::vector<std::string> fx = {"Glow", "Thunder", "Magic", "Rift"};
        for (size_t i = 0; i < fx.size(); ++i) {
            auto btn = CCMenuItemSpriteExtra::create(
                ButtonSprite::create(fx[i].c_str(), "goldFont.fnt", "GJ_button_01.png", 0.4f),
                this, menu_selector(ProArchitectUIDock::onInstantTriggerEffect)
            );
            btn->setTag(static_cast<int>(i));
            btn->setPosition({-145.0f + (i * 95.0f), 20.0f});
            m_buttonMenu->addChild(btn);
        }

        auto runBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("GENERATE", "goldFont.fnt", "GJ_button_01.png", 0.7f),
            this, menu_selector(ProArchitectUIDock::onTriggerExecution)
        );
        runBtn->setPosition({140, -115});
        m_buttonMenu->addChild(runBtn);

        this->setTouchEnabled(true);
        this->setKeypadEnabled(true);
        return true;
    }

    void onBrushChange(CCObject* s) { m_activeBrush = s->getTag(); Notification::create("Brush Selected!", NotificationIcon::Success)->show(); }
    void onInstantTriggerEffect(CCObject* s) { ProArchitectEngine::injectEffectSystem(m_editor, 500.0f, 150.0f, (EffectStyle)s->getTag()); Notification::create("FX Spawned!", NotificationIcon::Success)->show(); }
    void onTriggerExecution(CCObject*) {
        float stepX = (60.0f / 120.0f) * 311.58f;
        auto blocks = ProArchitectEngine::get22Blocks();
        for (int i = 0; i < 80; i++) {
            float x = 500.0f + (i * stepX);
            m_editor->createObject(blocks[rand() % blocks.size()], {x, 75.0f}, true);
        }
        ProArchitectEngine::buildDynamicEndScreen(m_editor, 500.0f + (81 * stepX), 105.0f, CINEMATIC_SLOMO);
        onClose(nullptr);
    }
    void onClose(CCObject*) { this->removeFromParentAndCleanup(true); }
};

// ==========================================
// 🟡 COMPILER-SAFE DRAGGABLE HANDLER
// ==========================================
class OmniDragHandler : public CCNode, public CCTouchDelegate {
    CCPoint m_lastPos;
    bool m_isDragging = false;
    CCMenu* m_target;
public:
    static OmniDragHandler* create(CCMenu* target) {
        auto ret = new OmniDragHandler();
        ret->m_target = target;
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret); return nullptr;
    }

    bool init() override {
        // We use the Director to handle touches manually to bypass CCNode limitations
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -500, true);
        return true;
    }

    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override {
        auto pos = touch->getLocation();
        // Check if the AI button was hit
        if (m_target->getChildByTag(69)->boundingBox().containsPoint(m_target->convertToNodeSpace(pos))) {
            m_lastPos = pos;
            m_isDragging = false;
            return true;
        }
        return false;
    }

    void ccTouchMoved(CCTouch* touch, CCEvent* event) override {
        m_isDragging = true;
        auto pos = touch->getLocation();
        m_target->setPosition(m_target->getPosition() + (pos - m_lastPos));
        m_lastPos = pos;
    }

    void ccTouchEnded(CCTouch* touch, CCEvent* event) override {
        if (!m_isDragging && g_omniEditor) ProArchitectUIDock::create(g_omniEditor)->show();
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

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        auto menu = CCMenu::create();
        menu->setPosition({winSize.width / 2, winSize.height - 40});
        
        auto spr = ButtonSprite::create("AI", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        auto btn = CCMenuItemSpriteExtra::create(spr, this, nullptr);
        btn->setTag(69); 
        
        menu->addChild(btn);
        this->addChild(menu, 1000);

        auto handler = OmniDragHandler::create(menu);
        this->addChild(handler);

        return true;
    }
};
