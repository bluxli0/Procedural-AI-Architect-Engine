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

enum EffectStyle {
    CLASSIC_GLOW = 0,
    THUNDER_STORM = 1,
    MAGIC_GLOW = 2,
    MYTHIC_PORTAL = 3
};

enum DrawBrush {
    SOLID_BLOCK = 0,
    DECORATION_LINE = 1,
    SPIKE_CHAIN = 2,
    GRADIENT_3D_ILLUSION = 3
};

enum EndTheme {
    CINEMATIC_SLOMO = 0,
    TEXT_CREDIT_REEL = 1,
    QUANTUM_SINGULARITY = 2
};

// ==========================================
// 🧠 CO-CREATOR MASTER OMNI-ENGINE CORE
// ==========================================
class ProArchitectEngine {
public:
    static ColorHarmony generateHarmonicPalette(float baseHue) {
        auto hsvToRgb = [](float h, float s, float v) -> cocos2d::ccColor3B {
            h = std::fmod(h, 360.0f);
            if (h < 0.0f) h += 360.0f;

            float c = v * s;
            float x = c * (1.0f - std::fabs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
            float m = v - c;

            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;

            if (h < 60.0f) {
                r = c;
                g = x;
            } else if (h < 120.0f) {
                r = x;
                g = c;
            } else if (h < 180.0f) {
                g = c;
                b = x;
            } else if (h < 240.0f) {
                g = x;
                b = c;
            } else if (h < 300.0f) {
                r = x;
                b = c;
            } else {
                r = c;
                b = x;
            }

            return {
                static_cast<GLubyte>((r + m) * 255),
                static_cast<GLubyte>((g + m) * 255),
                static_cast<GLubyte>((b + m) * 255)
            };
        };

        return {
            hsvToRgb(baseHue, 0.85f, 0.9f),
            hsvToRgb(baseHue + 120.0f, 0.75f, 0.8f),
            hsvToRgb(baseHue + 240.0f, 0.95f, 0.95f)
        };
    }

    static void injectEffectSystem(LevelEditorLayer* editor, float x, float y, EffectStyle style) {
        if (!editor) return;

        switch (style) {
            case CLASSIC_GLOW:
                editor->createObject(221, {x, y + 20.0f}, true);
                break;

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
            float offset = i * 6.0f;

            if (auto slice = editor->createObject(1, {startX + offset, startY + offset}, true)) {
                slice->setScale(scale);
                slice->setZOrder(i);
            }
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

            case TEXT_CREDIT_REEL:
                editor->createObject(3910, {x, y + 80.0f}, true);
                break;

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
    LevelEditorLayer* m_editor = nullptr;

    int m_activeBrush = 0;
    int m_activeEffect = 0;
    int m_activeEndTheme = 0;

    float m_paletteHue = 180.0f;

    CCLabelBMFont* m_lblHue = nullptr;
    CCLabelBMFont* m_lblEndTheme = nullptr;
    cocos2d::CCNode* m_palettePreviewNode = nullptr;

    bool init(LevelEditorLayer* editor) {
        if (!FLAlertLayer::init(220)) return false;

        m_editor = editor;

        auto winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

        auto mainLayer = cocos2d::CCNode::create();
        this->addChild(mainLayer);

        auto bg = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png");
        if (bg) {
            bg->setContentSize({420.0f, 320.0f});
            bg->setPosition(winSize / 2);
            mainLayer->addChild(bg);
        }

        auto menu = cocos2d::CCMenu::create();
        menu->setPosition({0.0f, 0.0f});
        this->addChild(menu);

        auto closeBtn = CCMenuItemSpriteExtra::create(
            cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
            this,
            menu_selector(ProArchitectUIDock::onClose)
        );
        closeBtn->setPosition(winSize.width / 2 - 195.0f, winSize.height / 2 + 145.0f);
        menu->addChild(closeBtn);

        auto title = CCLabelBMFont::create("AI ARCHITECT OMNI-PANEL", "goldFont.fnt");
        title->setPosition(winSize.width / 2, winSize.height / 2 + 135.0f);
        title->setScale(0.65f);
        mainLayer->addChild(title);

        // --- BRUSHES ---
        std::vector<std::string> brushes = {"Block", "Pipe", "Spikes", "3D"};
        for (size_t i = 0; i < brushes.size(); ++i) {
            auto btn = CCMenuItemSpriteExtra::create(
                ButtonSprite::create(
                    brushes[i].c_str(),
                    "goldFont.fnt",
                    "GJ_button_04.png",
                    0.4f
                ),
                this,
                menu_selector(ProArchitectUIDock::onBrushChange)
            );

            btn->setTag(static_cast<int>(i));
            btn->setPosition(winSize.width / 2 - 145.0f + (i * 95.0f), winSize.height / 2 + 80.0f);
            menu->addChild(btn);
        }

        // --- FX TRIGGERS ---
        std::vector<std::string> effects = {"Glow", "Thunder", "Magic", "Rift"};
        for (size_t i = 0; i < effects.size(); ++i) {
            auto btn = CCMenuItemSpriteExtra::create(
                ButtonSprite::create(
                    effects[i].c_str(),
                    "goldFont.fnt",
                    "GJ_button_01.png",
                    0.4f
                ),
                this,
                menu_selector(ProArchitectUIDock::onInstantTriggerEffect)
            );

            btn->setTag(static_cast<int>(i));
            btn->setPosition(winSize.width / 2 - 145.0f + (i * 95.0f), winSize.height / 2 + 20.0f);
            menu->addChild(btn);
        }

        // --- END DESIGNER ---
        m_lblEndTheme = CCLabelBMFont::create("Theme: Cinematic", "bigFont.fnt");
        m_lblEndTheme->setPosition(winSize.width / 2 - 110.0f, winSize.height / 2 - 40.0f);
        m_lblEndTheme->setScale(0.35f);
        mainLayer->addChild(m_lblEndTheme);

        auto cycleEndBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                "CYCLE END",
                "goldFont.fnt",
                "GJ_button_03.png",
                0.4f
            ),
            this,
            menu_selector(ProArchitectUIDock::onCycleEndTheme)
        );
        cycleEndBtn->setPosition(winSize.width / 2 - 110.0f, winSize.height / 2 - 65.0f);
        menu->addChild(cycleEndBtn);

        // --- COLOR THEORY ---
        m_lblHue = CCLabelBMFont::create("H: 180°", "bigFont.fnt");
        m_lblHue->setPosition(winSize.width / 2 + 65.0f, winSize.height / 2 - 40.0f);
        m_lblHue->setScale(0.38f);
        mainLayer->addChild(m_lblHue);

        auto subHueBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create("<", "bigFont.fnt", "GJ_button_02.png", 0.35f),
            this,
            menu_selector(ProArchitectUIDock::onReduceHue)
        );
        subHueBtn->setPosition(winSize.width / 2 + 125.0f, winSize.height / 2 - 40.0f);
        menu->addChild(subHueBtn);

        auto addHueBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(">", "bigFont.fnt", "GJ_button_02.png", 0.35f),
            this,
            menu_selector(ProArchitectUIDock::onIncreaseHue)
        );
        addHueBtn->setPosition(winSize.width / 2 + 155.0f, winSize.height / 2 - 40.0f);
        menu->addChild(addHueBtn);

        m_palettePreviewNode = cocos2d::CCNode::create();
        m_palettePreviewNode->setPosition(winSize.width / 2 + 65.0f, winSize.height / 2 - 65.0f);
        mainLayer->addChild(m_palettePreviewNode);
        updatePalettePreview();

        // --- UTILS ---
        auto cleanBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                "WIPE CANVAS",
                "goldFont.fnt",
                "GJ_button_06.png",
                0.5f
            ),
            this,
            menu_selector(ProArchitectUIDock::onClearObjects)
        );
        cleanBtn->setPosition(winSize.width / 2 - 120.0f, winSize.height / 2 - 115.0f);
        menu->addChild(cleanBtn);

        auto resetDefaultsBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                "RESET DEFAULTS",
                "goldFont.fnt",
                "GJ_button_05.png",
                0.45f
            ),
            this,
            menu_selector(ProArchitectUIDock::onResetSystemDefaults)
        );
        resetDefaultsBtn->setPosition(winSize.width / 2 + 10.0f, winSize.height / 2 - 115.0f);
        menu->addChild(resetDefaultsBtn);

        auto runBtn = CCMenuItemSpriteExtra::create(
            ButtonSprite::create(
                "GENERATE",
                "goldFont.fnt",
                "GJ_button_01.png",
                0.52f
            ),
            this,
            menu_selector(ProArchitectUIDock::onTriggerExecution)
        );
        runBtn->setPosition(winSize.width / 2 + 130.0f, winSize.height / 2 - 115.0f);
        menu->addChild(runBtn);

        this->setTouchEnabled(true);
        this->setKeyboardEnabled(true);

        return true;
    }

    void updatePalettePreview() {
        if (!m_palettePreviewNode) return;

        m_palettePreviewNode->removeAllChildrenWithCleanup(true);

        ColorHarmony pal = ProArchitectEngine::generateHarmonicPalette(m_paletteHue);
        std::vector<cocos2d::ccColor3B> cols = {
            pal.primary,
            pal.secondary,
            pal.accent
        };

        for (size_t i = 0; i < cols.size(); ++i) {
            auto b = cocos2d::CCSprite::createWithSpriteFrameName("square_01_001.png");
            if (!b) continue;

            b->setColor(cols[i]);
            b->setScale(0.5f);
            b->setPositionX(static_cast<float>(i * 25.0f));
            m_palettePreviewNode->addChild(b);
        }
    }

    void onReduceHue(CCObject*) {
        m_paletteHue -= 15.0f;
        if (m_paletteHue < 0.0f) m_paletteHue += 360.0f;

        if (m_lblHue) {
            m_lblHue->setString(("H: " + std::to_string(static_cast<int>(m_paletteHue)) + "°").c_str());
        }

        updatePalettePreview();
    }

    void onIncreaseHue(CCObject*) {
        m_paletteHue += 15.0f;
        if (m_paletteHue >= 360.0f) m_paletteHue -= 360.0f;

        if (m_lblHue) {
            m_lblHue->setString(("H: " + std::to_string(static_cast<int>(m_paletteHue)) + "°").c_str());
        }

        updatePalettePreview();
    }

    void onCycleEndTheme(CCObject*) {
        m_activeEndTheme = (m_activeEndTheme + 1) % 3;

        const char* names[3] = {
            "Cinematic",
            "Credits",
            "Singularity"
        };

        if (m_lblEndTheme) {
            m_lblEndTheme->setString((std::string("Theme: ") + names[m_activeEndTheme]).c_str());
        }
    }

    void onResetSystemDefaults(CCObject*) {
        m_activeBrush = 0;
        m_activeEffect = 0;
        m_activeEndTheme = 0;
        m_paletteHue = 180.0f;

        if (m_lblHue) m_lblHue->setString("H: 180°");
        if (m_lblEndTheme) m_lblEndTheme->setString("Theme: Cinematic");

        updatePalettePreview();

        Notification::create(
            "Defaults Restored!",
            NotificationIcon::Success,
            1.2f
        )->show();
    }

    void onBrushChange(CCObject* sender) {
        if (!sender) return;

        m_activeBrush = sender->getTag();

        Notification::create(
            "Brush selected",
            NotificationIcon::Success,
            0.8f
        )->show();
    }

    void onInstantTriggerEffect(CCObject* sender) {
        if (!m_editor || !sender) return;

        int fx = sender->getTag();

        // Safe fixed anchor near level start
        float tx = 500.0f + (fx * 120.0f);

        ProArchitectEngine::injectEffectSystem(
            m_editor,
            tx,
            150.0f,
            static_cast<EffectStyle>(fx)
        );

        Notification::create(
            "Effect Generated @ x≈500",
            NotificationIcon::Success,
            1.0f
        )->show();
    }

    void onClearObjects(CCObject*) {
        // Safe no-op for now; avoids private object array access.
        Notification::create(
            "Wipe disabled in safe build",
            NotificationIcon::Info,
            1.2f
        )->show();
    }

    void onTriggerExecution(CCObject*) {
        if (!m_editor) return;

        float stepX = (60.0f / 120.0f) * 311.58f;

        for (int i = 0; i < 80; ++i) {
            float x = 500.0f + (i * stepX);

            if (m_activeBrush == GRADIENT_3D_ILLUSION) {
                ProArchitectEngine::buildIsometric3DShape(
                    m_editor,
                    x,
                    105.0f,
                    4
                );
            } else {
                int brushID =
                    (m_activeBrush == SOLID_BLOCK) ? 1 :
                    (m_activeBrush == DECORATION_LINE) ? 940 :
                    (m_activeBrush == SPIKE_CHAIN) ? 8 :
                    1;

                m_editor->createObject(
                    brushID,
                    {x, 75.0f},
                    true
                );
            }

            if (i % 16 == 0) {
                ProArchitectEngine::injectEffectSystem(
                    m_editor,
                    x,
                    105.0f,
                    static_cast<EffectStyle>(m_activeEffect)
                );
            }
        }

        ProArchitectEngine::buildDynamicEndScreen(
            m_editor,
            500.0f + (81.0f * stepX),
            105.0f,
            static_cast<EndTheme>(m_activeEndTheme)
        );

        this->onClose(nullptr);
    }

    void onClose(CCObject*) {
        this->removeFromParentAndCleanup(true);
    }

public:
    static ProArchitectUIDock* create(LevelEditorLayer* editor) {
        auto ret = new ProArchitectUIDock();

        if (ret && ret->init(editor)) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

// ==========================================
// 🟡 DRAGGABLE FLOATING OMNI BUTTON
// ==========================================
class OmniFloatingButton : public cocos2d::CCLayer {
protected:
    cocos2d::CCPoint m_touchStart;
    cocos2d::CCPoint m_nodeStart;
    bool m_dragged = false;

    bool init() {
        if (!cocos2d::CCLayer::init()) return false;

        this->setContentSize({64.0f, 64.0f});
        this->setAnchorPoint({0.5f, 0.5f});
        this->setID("omni-floating-drag-button");

        auto circle = cocos2d::CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");

        if (!circle) {
            circle = cocos2d::CCSprite::createWithSpriteFrameName("GJ_editBtn_001.png");
        }

        if (circle) {
            circle->setPosition({32.0f, 32.0f});
            circle->setScale(0.95f);
            this->addChild(circle);
        }

        auto label = CCLabelBMFont::create("AI", "goldFont.fnt");
        label->setScale(0.55f);
        label->setPosition({32.0f, 32.0f});
        this->addChild(label, 2);

        this->setTouchEnabled(true);

        return true;
    }

    void registerWithTouchDispatcher() override {
        cocos2d::CCDirector::sharedDirector()
            ->getTouchDispatcher()
            ->addTargetedDelegate(this, -500, true);
    }

    bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent*) override {
        auto location = this->convertToNodeSpace(touch->getLocation());
        auto rect = cocos2d::CCRect(0.0f, 0.0f, 64.0f, 64.0f);

        if (!rect.containsPoint(location)) {
            return false;
        }

        m_touchStart = touch->getLocation();
        m_nodeStart = this->getPosition();
        m_dragged = false;

        return true;
    }

    void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent*) override {
        auto now = touch->getLocation();
        auto delta = now - m_touchStart;

        if (std::abs(delta.x) > 4.0f || std::abs(delta.y) > 4.0f) {
            m_dragged = true;
        }

        this->setPosition(m_nodeStart + delta);
    }

    void ccTouchEnded(cocos2d::CCTouch*, cocos2d::CCEvent*) override {
        if (m_dragged) return;

        if (!g_omniEditor) {
            Notification::create(
                "Editor not ready",
                NotificationIcon::Info,
                1.2f
            )->show();

            log::warn("[Omni] Floating button tapped, but editor handle is null.");
            return;
        }

        log::info("[Omni] Floating button tapped. Opening panel.");

        if (auto panel = ProArchitectUIDock::create(g_omniEditor)) {
            panel->show();
        }
    }

public:
    static OmniFloatingButton* create() {
        auto ret = new OmniFloatingButton();

        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

// ==========================================
// 🧩 HOOK: STORE CURRENT EDITOR
// ==========================================
class $modify(OmniLevelEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* level, bool p1) {
        if (!LevelEditorLayer::init(level, p1)) return false;

        g_omniEditor = this;

        log::info("[Omni] LevelEditorLayer stored.");

        return true;
    }
};

// ==========================================
// 🧩 HOOK: ADD FLOATING BUTTON TO EDITOR UI
// ==========================================
class $modify(OmniEditorUI, EditorUI) {
    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorUI::init(editorLayer)) return false;

        g_omniEditor = editorLayer;

        this->runAction(cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(0.05f),
            cocos2d::CCCallFunc::create(
                this,
                callfunc_selector(OmniEditorUI::addOmniFloatingButton)
            ),
            nullptr
        ));

        return true;
    }

    void addOmniFloatingButton() {
        if (this->getChildByID("omni-floating-drag-button")) {
            log::info("[Omni] Floating button already exists; skipping duplicate.");
            return;
        }

        auto win = cocos2d::CCDirector::sharedDirector()->getWinSize();

        auto button = OmniFloatingButton::create();

        if (!button) {
            log::error("[Omni] Failed to create floating button.");
            return;
        }

        // Default spawn: top-centre
        button->setPosition({
            win.width / 2.0f,
            win.height - 55.0f
        });

        this->addChild(button, 999999);

        log::info("[Omni] Floating draggable AI button added at top-centre.");

        Notification::create(
            "Omni loaded — drag/tap AI",
            NotificationIcon::Success,
            1.5f
        )->show();
    }
};
