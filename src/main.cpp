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

enum EffectStyle { GLOW = 0, THUNDER = 1, MAGIC = 2, RIFT = 3 };

// ==========================================
// 🧠 CO-CREATOR MASTER OMNI-ENGINE CORE
// ==========================================
class ProArchitectEngine {
public:
    static void injectEffectSystem(LevelEditorLayer* editor, float x, float y, EffectStyle style) {
        if (!editor) return;
        int ids[] = {221, 2397, 2391, 8520};
        editor->createObject(ids[style], {x, y}, true);
    }
};

// ==========================================
// 🎨 INTEGRATED MASTER INTERACTION PANEL
// ==========================================
class ProArchitectUIDock : public FLAlertLayer {
    LevelEditorLayer* m_editor;
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
        if (!FLAlertLayer::init(150)) return false;
        m_editor = editor;
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        auto bg = CCScale9Sprite::create("GJ_square01.png");
        bg->setContentSize({380, 220});
        bg->setPosition(winSize / 2);
        m_mainLayer->addChild(bg);

        auto menu = CCMenu::create();
        m_mainLayer->addChild(menu);

        auto closeBtn = CCMenuItemSpriteExtra::create(
            CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
            this, menu_selector(ProArchitectUIDock::onClose));
        closeBtn->setPosition({-175, 95});
        menu->addChild(closeBtn);

        auto title = CCLabelBMFont::create("OMNI ARCHITECT PRO", "goldFont.fnt");
        title->setPosition(winSize.width / 2, winSize.height / 2 + 85);
        m_mainLayer->addChild(title);

        auto genBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("BUILD", "goldFont.fnt", "GJ_button_01.png", 0.8f),
            this, menu_selector(ProArchitectUIDock::onRun));
        genBtn->setPosition({0, -60});
        menu->addChild(genBtn);

        return true;
    }

    void onClose(CCObject*) { this->removeFromParentAndCleanup(true); }
    void onRun(CCObject*) {
        ProArchitectEngine::injectEffectSystem(m_editor, 500, 150, GLOW);
        Notification::create("Build Success!", NotificationIcon::Success)->show();
        onClose(nullptr);
    }
};

// ==========================================
// 🟡 DRAGGABLE CONTROLLER (COMPILER SAFE)
// ==========================================
class OmniDragHandler : public CCNode {
    CCPoint m_lastPos;
    bool m_isDragging = false;
    CCMenu* m_targetMenu;

public:
    static OmniDragHandler* create(CCMenu* target) {
        auto ret = new OmniDragHandler();
        ret->m_targetMenu = target;
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret); return nullptr;
    }

    bool init() override {
        this->setTouchEnabled(true);
        return true;
    }

    // Capture the touch events for the parent menu
    void registerWithTouchDispatcher() override {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -500, true);
    }

    bool ccTouchBegan(CCTouch* touch, CCEvent* event) override {
        auto pos = touch->getLocation();
        if (m_targetMenu->getChildByTag(69)->boundingBox().containsPoint(m_targetMenu->convertToNodeSpace(pos))) {
            m_lastPos = pos;
            m_isDragging = false;
            return true;
        }
        return false;
    }

    void ccTouchMoved(CCTouch* touch, CCEvent* event) override {
        m_isDragging = true;
        auto pos = touch->getLocation();
        m_targetMenu->setPosition(m_targetMenu->getPosition() + (pos - m_lastPos));
        m_lastPos = pos;
    }

    void ccTouchEnded(CCTouch* touch, CCEvent* event) override {
        if (!m_isDragging && g_omniEditor) {
            ProArchitectUIDock::create(g_omniEditor)->show();
        }
        m_isDragging = false;
    }
};

// ==========================================
// 🧩 GAME HOOKS
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
        btn->setTag(69); // ID for the drag handler to find
        
        menu->addChild(btn);
        this->addChild(menu, 1000);

        // Add the Draggable Brain
        auto handler = OmniDragHandler::create(menu);
        this->addChild(handler);

        return true;
    }
};
