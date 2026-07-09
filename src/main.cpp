#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/utils/cocos.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace geode::prelude;

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
    // Generates a clean 3-color palette using harmonic trisection math
    static ColorHarmony generateHarmonicPalette(float baseHue) {
        auto hsvToRgb = [](float h, float s, float v) -> cocos2d::ccColor3B {
            h = fmod(h, 360.0f);
            if (h < 0.0f) h += 360.0f;
            
            float c = v * s;
            float x = c * (1.0f - fabs(fmod(h / 60.0f, 2.0f) - 1.0f));
            float m = v - c;
            float r = 0, g = 0, b = 0;
            
            if (h < 60.0f)        { r = c; g = x; }
            else if (h < 120.0f)  { r = x; g = c; }
            else if (h < 180.0f)  { g = c; b = x; }
            else if (h < 240.0f)  { g = x; b = c; }
            else if (h < 300.0f)  { r = x; b = c; }
            else                  { r = c; b = x; }
            
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

    // Injects highly styled, stacked visual effect groups
    static void injectEffectSystem(LevelEditorLayer* editor, float x, float y, EffectStyle style) {
        if (!editor) return;
        switch (style) {
            case CLASSIC_GLOW: {
                if (auto obj = editor->createObject(221, {x, y + 20.0f}, true)) {
                    editor->addObject(obj);
                }
                break;
            }
            case THUNDER_STORM: {
                if (auto shake = editor->createObject(1520, {x, y}, true)) {
                    editor->addObject(shake);
                }
                if (auto glitch = editor->createObject(2397, {x, y + 100.0f}, true)) {
                    editor->addObject(glitch);
                }
                break;
            }
            case MAGIC_GLOW: {
                if (auto gradient = editor->createObject(2391, {x, y + 300.0f}, true)) {
                    editor->addObject(gradient);
                }
                if (auto sparkle = editor->createObject(2614, {x, y + 50.0f}, true)) {
                    editor->addObject(sparkle);
                }
                break;
            }
            case MYTHIC_PORTAL: {
                if (auto rBlur = editor->createObject(2400, {x, y + 150.0f}, true)) {
                    editor->addObject(rBlur);
                }
                if (auto rift = editor->createObject(8520, {x, y + 50.0f}, true)) {
                    editor->addObject(rift);
                }
                break;
            }
        }
    }

    // Builds 2.2-compliant 3D isometric illusions
    static void buildIsometric3DShape(LevelEditorLayer* editor, float startX, float startY, int slices) {
        if (!editor) return;
        for (int i = 0; i < slices; i++) {
            float scale = 1.0f - (i * 0.15f);
            float offset = i * 6.0f;
            
            auto slice = editor->createObject(1, {startX + offset, startY + offset}, true);
            if (!slice) continue;
            
            slice->setScale(scale);
            slice->setZOrder(i);
            editor->addObject(slice);
        }
        
        if (auto gradTrig = editor->createObject(2391, {startX, startY + 100.0f}, true)) {
            editor->addObject(gradTrig);
        }
    }

    // Injects highly cinematic procedural endings
    static void buildDynamicEndScreen(LevelEditorLayer* editor, float x, float y, EndTheme theme) {
        if (!editor) return;
        
        // Spawn the end level object boundary (ID 1979)
        if (auto endBorder = editor->createObject(1979, {x + 150.0f, y}, true)) {
            editor->addObject(endBorder);
        }

        switch (theme) {
            case CINEMATIC_SLOMO: {
                // Drop Time Warp (ID 1915) configured slow + ambient warm Color triggers (ID 899)
                if (auto tw = editor->createObject(1915, {x, y}, true)) {
                    editor->addObject(tw);
                }
                if (auto col = editor->createObject(899, {x - 30.0f, y}, true)) {
                    editor->addObject(col);
                }
                break;
            }
            case TEXT_CREDIT_REEL: {
                // Spawn a custom 2.2 UI Text Marker Card (ID 3910)
                if (auto textCard = editor->createObject(3910, {x, y + 80.0f}, true)) {
                    editor->addObject(textCard);
                }
                break;
            }
            case QUANTUM_SINGULARITY: {
                // Spawn Event Horizon Void (ID 8505) and Reality Distortion filters (ID 8510)
                if (auto horizon = editor->createObject(8505, {x, y}, true)) {
                    editor->addObject(horizon);
                }
                if (auto distort = editor->createObject(8510, {x - 10.0f, y}, true)) {
                    editor->addObject(distort);
                }
                break;
            }
        }
    }
};

// ==========================================
// 🎨 INTEGRATED MASTER INTERACTION CANVAS
// ==========================================
class ProArchitectUIDock : public FLAlertLayer {
protected:
    LevelEditorLayer* m_editor;
    
    // User Configurator Variables
    int m_activeBrush = 0;
    int m_activeEffect = 0;
    int m_activeEndTheme = 0;
    float m_paletteHue = 180.0f; 

    CCLabelBMFont* m_lblHue = nullptr;
    CCLabelBMFont* m_lblEndTheme = nullptr;
    cocos2d::CCNode* m_palettePreviewNode = nullptr;

    bool init(LevelEditorLayer* editor) {
        // Comfortably scale layout parameters (Expanded structure boundaries)
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
        menu->setPosition({0, 0});
        this->addChild(menu);

        // Exit Anchor
        auto closeSprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
        auto closeBtn = CCMenuItemSpriteExtra::create(
            closeSprite, this, menu_selector(ProArchitectUIDock::onClose)
        );
        closeBtn->setPosition(winSize.width / 2 - 195.0f, winSize.height / 2 + 145.0f);
        menu->addChild(closeBtn);

        // Header
        auto title = CCLabelBMFont::create("OMNI-ARCHITECT CO-CREATOR PANEL", "goldFont.fnt");
        title->setPosition(winSize.width / 2, winSize.height / 2 + 135.0f);
        title->setScale(0.65f);
        mainLayer->addChild(title);

        // --- ROW 1: THEME BRUSH PIPELINES ---
        auto brushLabel = CCLabelBMFont::create("BRUSH SELECTION", "bigFont.fnt");
        brushLabel->setPosition(winSize.width / 2 - 110.0f, winSize.height / 2 + 105.0f);
        brushLabel->setScale(0.35f);
        mainLayer->addChild(brushLabel);

        std::vector<std::string> brushes = {"Block", "Pipe Decor", "Spikes", "3D Illusion"};
        for (size_t i = 0; i < brushes.size(); ++i) {
            auto btnSprite = ButtonSprite::create(brushes[i].c_str(), "goldFont.fnt", "GJ_button_04.png", 0.4f);
            auto brushBtn = CCMenuItemSpriteExtra::create(
                btnSprite, this, menu_selector(ProArchitectUIDock::onBrushChange)
            );
            brushBtn->setTag(static_cast<int>(i));
            brushBtn->setPosition(winSize.width / 2 - 145.0f + (i * 95.0f), winSize.height / 2 + 80.0f);
            menu->addChild(brushBtn);
        }

        // --- ROW 2: ENVIRONMENT EFFECTS ---
        auto effectLabel = CCLabelBMFont::create("LIVE ENVIRONMENTAL INSTANT FX", "bigFont.fnt");
        effectLabel->setPosition(winSize.width / 2 - 110.0f, winSize.height / 2 + 45.0f);
        effectLabel->setScale(0.35f);
        mainLayer->addChild(effectLabel);

        std::vector<std::string> effects = {"Glow", "Thunder", "Magic Glow", "Mythic Rift"};
        for (size_t i = 0; i < effects.size(); ++i) {
            auto btnSprite = ButtonSprite::create(effects[i].c_str(), "goldFont.fnt", "GJ_button_01.png", 0.4f);
            auto effectBtn = CCMenuItemSpriteExtra::create(
                btnSprite, this, menu_selector(ProArchitectUIDock::onInstantTriggerEffect)
            );
            effectBtn->setTag(static_cast<int>(i));
            effectBtn->setPosition(winSize.width / 2 - 145.0f + (i * 95.0f), winSize.height / 2 + 20.0f);
            menu->addChild(effectBtn);
        }

        // --- COLUMN 3A: THE PROGRESSIVE ENDING DESIGNER ---
        auto endingLabel = CCLabelBMFont::create("DASHBOARD END SCREEN", "bigFont.fnt");
        endingLabel->setPosition(winSize.width / 2 - 110.0f, winSize.height / 2 - 15.0f);
        endingLabel->setScale(0.35f);
        mainLayer->addChild(endingLabel);

        m_lblEndTheme = CCLabelBMFont::create("Theme: Cinematic", "bigFont.fnt");
        m_lblEndTheme->setPosition(winSize.width / 2 - 110.0f, winSize.height / 2 - 40.0f);
        m_lblEndTheme->setScale(0.35f);
        m_lblEndTheme->setColor({255, 125, 0});
        mainLayer->addChild(m_lblEndTheme);

        auto cycleEndSpr = ButtonSprite::create("CYCLE THEME", "goldFont.fnt", "GJ_button_03.png", 0.4f);
        auto cycleEndBtn = CCMenuItemSpriteExtra::create(
            cycleEndSpr, this, menu_selector(ProArchitectUIDock::onCycleEndTheme)
        );
        cycleEndBtn->setPosition(winSize.width / 2 - 110.0f, winSize.height / 2 - 65.0f);
        menu->addChild(cycleEndBtn);

        // --- COLUMN 3B: HARMONIC HUED GENERATOR ---
        auto paletteLabel = CCLabelBMFont::create("COLOR THEORY ENGINE", "bigFont.fnt");
        paletteLabel->setPosition(winSize.width / 2 + 110.0f, winSize.height / 2 - 15.0f);
        paletteLabel->setScale(0.35f);
        mainLayer->addChild(paletteLabel);

        m_lblHue = CCLabelBMFont::create("H: 180°", "bigFont.fnt");
        m_lblHue->setPosition(winSize.width / 2 + 65.0f, winSize.height / 2 - 40.0f);
        m_lblHue->setScale(0.38f);
        mainLayer->addChild(m_lblHue);

        auto subHueSpr = ButtonSprite::create("<", "bigFont.fnt", "GJ_button_02.png", 0.35f);
        auto subHueBtn = CCMenuItemSpriteExtra::create(subHueSpr, this, menu_selector(ProArchitectUIDock::onReduceHue));
        subHueBtn->setPosition(winSize.width / 2 + 125.0f, winSize.height / 2 - 40.0f);
        menu->addChild(subHueBtn);

        auto addHueSpr = ButtonSprite::create(">", "bigFont.fnt", "GJ_button_02.png", 0.35f);
        auto addHueBtn = CCMenuItemSpriteExtra::create(addHueSpr, this, menu_selector(ProArchitectUIDock::onIncreaseHue));
        addHueBtn->setPosition(winSize.width / 2 + 155.0f, winSize.height / 2 - 40.0f);
        menu->addChild(addHueBtn);

        m_palettePreviewNode = cocos2d::CCNode::create();
        m_palettePreviewNode->setPosition(winSize.width / 2 + 65.0f, winSize.height / 2 - 65.0f);
        mainLayer->addChild(m_palettePreviewNode);
        updatePalettePreview();

        // --- ROW 4: CONSOLE SYSTEM UTILITY BUTTONS (WIPE, DEFAULT RESET, RUN) ---
        // 1. Wipe Layout (Wipe Canvas)
        auto cleanSpr = ButtonSprite::create("WIPE LAYOUT", "goldFont.fnt", "GJ_button_06.png", 0.5f);
        auto cleanBtn = CCMenuItemSpriteExtra::create(
            cleanSpr, this, menu_selector(ProArchitectUIDock::onClearObjects)
        );
        cleanBtn->setPosition(winSize.width / 2 - 135.0f, winSize.height / 2 - 115.0f);
        menu->addChild(cleanBtn);

        // 2. Clear Visual Effects ONLY
        auto resetFXSpr = ButtonSprite::create("RESET FX", "goldFont.fnt", "GJ_button_05.png", 0.5f);
        auto resetFXBtn = CCMenuItemSpriteExtra::create(
            resetFXSpr, this, menu_selector(ProArchitectUIDock::onResetEffectsOnly)
        );
        resetFXBtn->setPosition(winSize.width / 2 - 50.0f, winSize.height / 2 - 115.0f);
        menu->addChild(resetFXBtn);

        // 3. Reset Dynamic Interface default values (Restore System Defaults Side Panel tool)
        auto restoreDefaultSpr = ButtonSprite::create("DEFAULT CONFIG", "goldFont.fnt", "GJ_button_05.png", 0.45f);
        auto restoreDefaultBtn = CCMenuItemSpriteExtra::create(
            restoreDefaultSpr, this, menu_selector(ProArchitectUIDock::onResetSystemDefaults)
        );
        restoreDefaultBtn->setPosition(winSize.width / 2 + 45.0f, winSize.height / 2 - 115.0f);
        menu->addChild(restoreDefaultBtn);

        // 4. Central Master Generator Trigger
        auto runSpr = ButtonSprite::create("BUILD SCENARIO", "goldFont.fnt", "GJ_button_01.png", 0.52f);
        auto runBtn = CCMenuItemSpriteExtra::create(
            runSpr, this, menu_selector(ProArchitectUIDock::onTriggerExecution)
        );
        runBtn->setPosition(winSize.width / 2 + 140.0f, winSize.height / 2 - 115.0f);
        menu->addChild(runBtn);

        this->setTouchEnabled(true);
        this->setKeyboardEnabled(true);

        return true;
    }

    void updatePalettePreview() {
        if (!m_palettePreviewNode) return;
        m_palettePreviewNode->removeAllChildrenWithCleanup(true);
        ColorHarmony pal = ProArchitectEngine::generateHarmonicPalette(m_paletteHue);

        std::vector<cocos2d::ccColor3B> previewColors = {pal.primary, pal.secondary, pal.accent};
        for (size_t i = 0; i < previewColors.size(); ++i) {
            auto block = cocos2d::CCSprite::createWithSpriteFrameName("square_01_001.png");
            if (!block) continue;
            block->setColor(previewColors[i]);
            block->setScale(0.5f);
            block->setPositionX(static_cast<float>(i * 25.0f));
            m_palettePreviewNode->addChild(block);
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
        std::vector<std::string> options = {"Cinematic", "Credit Reel", "Void Singularity"};
        if (m_lblEndTheme) {
            m_lblEndTheme->setString(("Theme: " + options[m_activeEndTheme]).c_str());
        }
    }

    // Direct interface values restoration
    void onResetSystemDefaults(CCObject*) {
        m_activeBrush = 0;
        m_activeEffect = 0;
        m_activeEndTheme = 0;
        m_paletteHue = 180.0f;

        if (m_lblHue) m_lblHue->setString("H: 180°");
        if (m_lblEndTheme) m_lblEndTheme->setString("Theme: Cinematic");
        updatePalettePreview();

        Notification::create("Engine Config Reset!", NotificationIcon::Success, 1.5f)->show();
    }

    void onBrushChange(CCObject* sender) {
        if (!sender) return;
        m_activeBrush = static_cast<CCMenuItemSpriteExtra*>(sender)->getTag();
    }

    void onEffectChange(CCObject* sender) {
        if (!sender) return;
        m_activeEffect = static_cast<CCMenuItemSpriteExtra*>(sender)->getTag();
    }

    void onInstantTriggerEffect(CCObject* sender) {
        if (!m_editor || !sender) return;
        
        int effectProfile = static_cast<CCMenuItemSpriteExtra*>(sender)->getTag();
        cocos2d::CCPoint cameraCenter = m_editor->m_objectLayer->getPosition();
        
        float targetX = -cameraCenter.x + (cocos2d::CCDirector::sharedDirector()->getWinSize().width / 2.0f);
        float targetY = 150.0f;

        ProArchitectEngine::injectEffectSystem(m_editor, targetX, targetY, static_cast<EffectStyle>(effectProfile));
        
        std::vector<std::string> profileNames = {"Classic Glow", "Thunder Storm", "Magic Glow", "Mythic Portal"};
        Notification::create(
            "SPAWNED: " + profileNames[effectProfile], 
            NotificationIcon::Success, 
            1.5f
        )->show();
    }

    void onClearObjects(CCObject*) {
        if (!m_editor) return;
        auto array = m_editor->m_objects;
        if (!array || array->count() == 0) return;

        for (int i = array->count() - 1; i >= 0; i--) {
            auto obj = static_cast<GameObject*>(array->objectAtIndex(i));
            if (obj && (obj->m_objectID == 1 || obj->m_objectID == 940 || obj->m_objectID == 2391 || obj->m_objectID == 8520 || obj->m_objectID == 221 || obj->m_objectID == 1520 || obj->m_objectID == 2397 || obj->m_objectID == 2614 || obj->m_objectID == 2400 || obj->m_objectID == 8505 || obj->m_objectID == 8510 || obj->m_objectID == 1979)) {
                m_editor->removeObject(obj, true);
            }
        }
        FLAlertLayer::create("Canvas Wipe", "Sweep completed!", "OK")->show();
    }

    void onResetEffectsOnly(CCObject*) {
        if (!m_editor) return;
        auto array = m_editor->m_objects;
        if (!array || array->count() == 0) return;

        int wipedCount = 0;
        for (int i = array->count() - 1; i >= 0; i--) {
            auto obj = static_cast<GameObject*>(array->objectAtIndex(i));
            if (obj) {
                int id = obj->m_objectID;
                if (id == 221 || id == 1520 || id == 2397 || id == 2391 || id == 2614 || id == 2400 || id == 8520 || id == 8510) {
                    m_editor->removeObject(obj, true);
                    wipedCount++;
                }
            }
        }
        
        Notification::create(
            "Wiped " + std::to_string(wipedCount) + " FX triggers", 
            NotificationIcon::Success, 
            1.5f
        )->show();
    }

    void onTriggerExecution(CCObject*) {
        if (!m_editor) return;
        float speedUnitsPerSec = 311.58f; 
        float stepX = (60.0f / 120.0f) * speedUnitsPerSec;
        float anchorX = 500.0f;

        // 1. Generate core layout using the selected design brushes
        for (int i = 0; i < 80; ++i) {
            float x = anchorX + (i * stepX);
            float y = 105.0f;

            if (m_activeBrush == GRADIENT_3D_ILLUSION) {
                ProArchitectEngine::buildIsometric3DShape(m_editor, x, y, 4);
            } else {
                int brushID = (m_activeBrush == SOLID_BLOCK) ? 1 : 940;
                if (auto obj = m_editor->createObject(brushID, {x, y - 30.0f}, true)) {
                    m_editor->addObject(obj);
                }
            }

            if (i % 16 == 0) {
                ProArchitectEngine::injectEffectSystem(m_editor, x, y, static_cast<EffectStyle>(m_activeEffect));
            }
        }

        // 2. Generate final procedural ending screen (using the End Screen Designer selections)
        float endAnchorX = anchorX + (81 * stepX);
        ProArchitectEngine::buildDynamicEndScreen(m_editor, endAnchorX, 105.0f, static_cast<EndTheme>(m_activeEndTheme));

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
// 🎨 GEODE EDITOR LAYER HOOK INTERFACES
// ==========================================
class $modify(ProEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* level, bool p1) {
        if (!LevelEditorLayer::init(level, p1)) return false;

        auto menu = this->getChildByID("editor-menus");
        if (!menu) return true;

        auto spr = ButtonSprite::create("OMNI BUILD", "goldFont.fnt", "GJ_button_01.png", 0.7f);
        auto btn = CCMenuItemSpriteExtra::create(
            spr, this, menu_selector(ProEditorLayer::onOpenProStudioDock)
        );
        btn->setID("pro-co-creator-btn");

        if (auto bottomMenu = menu->getChildByID("bottom-menu")) {
            bottomMenu->addChild(btn);
            bottomMenu->updateLayout();
        }

        return true;
    }

    void onOpenProStudioDock(CCObject*) {
        if (auto popup = ProArchitectUIDock::create(this)) {
            popup->show();
        }
    }

    // Handles live drawing when the player taps the editor screen
    virtual void tapButton(cocos2d::CCPoint touchPoint) {
        LevelEditorLayer::tapButton(touchPoint);
        
        float gridSnappedX = round(touchPoint.x / 30.0f) * 30.0f;
        float gridSnappedY = round(touchPoint.y / 30.0f) * 30.0f;

        if (auto touchBlock = this->createObject(1, {gridSnappedX, gridSnappedY}, true)) {
            this->addObject(touchBlock);
        }
    }
};
