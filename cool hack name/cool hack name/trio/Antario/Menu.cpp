#include "GUI\GUI.h"
#include "Settings.h"
#include "Hooks.h"

void Detach() { g_Settings.bCheatActive = false; }

ui::MenuMain nMenu;

void Save()
{
	switch (g_Settings.config.cfgNumber)
	{
	case 0:
		g_Settings.SaveSettings("1", &g_Settings);
		break;
	case 1:
		g_Settings.SaveSettings("2", &g_Settings);
		break;
	case 2:
		g_Settings.SaveSettings("3", &g_Settings);
		break;
	case 3:
		g_Settings.SaveSettings("4", &g_Settings);
		break;
	case 4:
		g_Settings.SaveSettings("5", &g_Settings);
		break;
	case 5:
		g_Settings.SaveSettings("6", &g_Settings);
		break;
	}
}

void Load()
{
	switch (g_Settings.config.cfgNumber)
	{
	case 0:
		g_Settings.LoadSettings("1", &g_Settings);
		break;
	case 1:
		g_Settings.LoadSettings("2", &g_Settings);
		break;
	case 2:
		g_Settings.LoadSettings("3", &g_Settings);
		break;
	case 3:
		g_Settings.LoadSettings("4", &g_Settings);
		break;
	case 4:
		g_Settings.LoadSettings("5", &g_Settings);
		break;
	case 5:
		g_Settings.LoadSettings("6", &g_Settings);
		break;
	}
}

void MenuMain::Initialize()
{
    auto mainWindow = std::make_shared<Window>("cool cheat name", SSize(550, 420), g_Fonts.pFontTahoma8, g_Fonts.pFontTahoma10);
    {
        auto tab1 = std::make_shared<Tab>("H", 2, mainWindow);
        {
            auto sectMain = tab1->AddSection("test sect 1", 1.2435f);
            {
				sectMain->AddText("text");
				sectMain->AddCheckBox("checkbox", &g_Settings.test.bCheckbox);
				sectMain->AddText("combo box");
				sectMain->AddCombo("combo", &g_Settings.test.iCombo, std::vector<std::string>{
					"item 1",
					"item 2",
					"item 3"
				});
				sectMain->AddMulti("multi", g_Settings.test.bMulti, std::vector<std::string>{
					"item 1",
					"item 2",
					"item 3"
				});
				sectMain->AddCheckBox("checkbox", &g_Settings.test.bCheckbox);
				sectMain->AddText("iq slider");
				sectMain->AddSlider("slider", "", &g_Settings.test.iSlider, 0, 100);
				sectMain->AddKeyBind("keybind", &g_Settings.test.btKeybind, &g_Settings.test.iKeybind);
				/*sectMain->AddList("listbox", 7, &g_Settings.test.iList, std::vector<std::string>{
					"item 1",
					"item 2",
					"item 3",
					"item 4",
					"item 5",
					"item 6",
					"item 7",
					"item 8",
					"item 9",
					"item 10"
				});*/
				sectMain->AddTextField("textfield", &g_Settings.test.strTextField);
            }

            auto legit = tab1->AddSection("legit", .4f);
            {
				legit->AddCheckBox("backtrack", &g_Settings.rage.bBacktrack);
            }

			auto sectMain2 = tab1->AddSection("anti-aim", .844f);
			{

			}

        } mainWindow->AddChild(tab1);  

        auto tab2 = std::make_shared<Tab>("D", 2, mainWindow);
        {
			auto players = tab2->AddSection("players", .749f);
			{
				players->AddColor("box color", &g_Settings.visuals.cBox);
				players->AddCheckBox("bounding box", &g_Settings.visuals.bBox);
				players->AddCheckBox("dynamic", &g_Settings.visuals.bDynamic);
				players->AddColor("name color", &g_Settings.visuals.cName);
				players->AddCheckBox("name", &g_Settings.visuals.bName);
				players->AddCheckBox("health", &g_Settings.visuals.bHealth);
				players->AddText("flags");
				players->AddMulti("flags", g_Settings.visuals.bFlags, std::vector<std::string>{
					"balance",
					"armor",
					"scoped",
					"flashed"
				  //"bomb"
				});
				players->AddColor("weapon icon color", &g_Settings.visuals.cWeaponIcon);
				players->AddCheckBox("weapon icon", &g_Settings.visuals.bWeaponIcon);
				players->AddColor("weapon name color", &g_Settings.visuals.cWeaponName);
				players->AddCheckBox("weapon name", &g_Settings.visuals.bWeaponName);
				players->AddColor("weapon ammo color", &g_Settings.visuals.cWeaponAmmo);
				players->AddCheckBox("weapon ammo", &g_Settings.visuals.bWeaponAmmo);
				players->AddCheckBox("dormant", &g_Settings.visuals.bDormant);
				players->AddColor("offscreen esp color", &g_Settings.visuals.cOffscreenESP);
				players->AddCheckBox("offscreen esp", &g_Settings.visuals.bOffscreenESP);
				players->AddColor("glow color", &g_Settings.visuals.cGlow);
				players->AddCheckBox("glow", &g_Settings.visuals.bGlow);
				players->AddColor("footstep esp color", &g_Settings.visuals.cSound);
				players->AddCheckBox("footstep esp", &g_Settings.visuals.bSound);	

				//players->AddColor("skeleton color", &g_Settings.visuals.cSkeleton);
				//players->AddCheckBox("skeleton", &g_Settings.visuals.bSkeleton);// <-- causes cham flickering
			}

			auto playermodels = tab2->AddSection("player models", .497f);
			{
				playermodels->AddColor("enemy chams", &g_Settings.visuals.cChams);
				playermodels->AddCheckBox("enemy chams", &g_Settings.visuals.bChams);
				playermodels->AddColor("enemy chams invis", &g_Settings.visuals.cChamsZ);
				playermodels->AddCheckBox("enemy chams invis", &g_Settings.visuals.bChamsZ);
				playermodels->AddText("chams material");
				playermodels->AddCombo("chams material", &g_Settings.visuals.iMaterial, std::vector<std::string>{
					"flat",
					"colored",
					"metallic"
				});
				//playermodels->AddColor("backtrack chams", &g_Settings.visuals.cBackTrack);
				//playermodels->AddCheckBox("backtrack chams", &g_Settings.visuals.bBackTrackChams);
				playermodels->AddColor("local chams", &g_Settings.visuals.cLocalChams);
				playermodels->AddCheckBox("local chams", &g_Settings.visuals.bLocalChams);
				playermodels->AddText("local chams material");
				playermodels->AddCombo("local chams material", &g_Settings.visuals.iMaterialLocal, std::vector<std::string>{
					"flat",
					"colored",
					"metallic"
				});
				playermodels->AddText("self transparency");
				playermodels->AddSlider("self transparency", "%", &g_Settings.visuals.iTransparency, 0, 100);
				playermodels->AddCheckBox("blend when scoped", &g_Settings.visuals.bBlend);
				playermodels->AddCheckBox("remove chams when scoped", &g_Settings.visuals.bChamsWhileScoped);
			}

			auto effects = tab2->AddSection("removals", .34f);
			{
				effects->AddCheckBox("remove flashbangs", &g_Settings.visuals.bNoFlash);
				effects->AddCheckBox("remove smoke", &g_Settings.visuals.bRemoveSmoke);
				effects->AddCheckBox("remove visual recoil", &g_Settings.visuals.bRemoveRecoil);
				effects->AddCheckBox("remove scope", &g_Settings.visuals.bRemoveScope);
				effects->AddCheckBox("disable post processing", &g_Settings.visuals.bDisablePostProcessing);
			}

			auto world = tab2->AddSection("world", .28);
			{
				world->AddColor("items color", &g_Settings.visuals.cItems);
				world->AddCheckBox("items", &g_Settings.visuals.bItems);
				world->AddColor("projectiles color", &g_Settings.visuals.cProjectiles);
				world->AddCheckBox("projectiles", &g_Settings.visuals.bProjectiles);
				world->AddColor("bomb color", &g_Settings.visuals.cBomb);
				world->AddCheckBox("bomb", &g_Settings.visuals.bBomb);
				world->AddCheckBox("nightmode", &g_Settings.visuals.bNightmode);
				world->AddCheckBox("full bright", &g_Settings.visuals.bFullBright);
			}

			auto other = tab2->AddSection("other", .623f);
			{
				other->AddCheckBox("bullet tracers", &g_Settings.visuals.bBulletTracer);
				other->AddColor("local color", &g_Settings.visuals.cLocalTracer);
				other->AddText("bullet tracer miss");
				other->AddColor("local hurt color", &g_Settings.visuals.cLocalHurt);
				other->AddText("bullet tracer hit");
				other->AddColor("enemy color", &g_Settings.visuals.cEnemyTracer);
				other->AddText("enemy bullet tracer");
				other->AddText("bullet tracers time");
				other->AddSlider("bullet tracers time", "s", &g_Settings.visuals.iTracerTime, 1, 10);
				other->AddCheckBox("force crosshair", &g_Settings.visuals.bForceCrosshair);
				//other->AddColor("grenade prediction", &g_Settings.visuals.cGrenadePred);
				//other->AddCheckBox("grenade prediction", &g_Settings.visuals.bGrenadePrediction);
				other->AddCheckBox("hitmarker", &g_Settings.visuals.bHitmarker);
				other->AddCheckBox("hitmarker sound", &g_Settings.visuals.bHitmarkerSound);
				other->AddText("thirdperson");
				other->AddSlider("thirdperson distance", "", &g_Settings.visuals.iThirdpersonDistance, 60, 300);
				other->AddKeyBind("thirdperson", &g_Settings.visuals.btThirdperonKeybind, &g_Settings.visuals.iThirdpersonKeybind);
				other->AddCheckBox("spectator thirdperson", &g_Settings.visuals.bSpecThirdperson);
				other->AddText("fov");
				other->AddSlider("fov", "", &g_Settings.visuals.iFov, 0, 50);
				other->AddText("thirdperson fov");
				other->AddSlider("thirdperson fov", "", &g_Settings.visuals.iThirdpersonFov, 0, 50);
			}
        } mainWindow->AddChild(tab2);

		auto tab3 = std::make_shared<Tab>("G", 2, mainWindow);
		{
			auto misc1 = tab3->AddSection("misc", .4f);
			{
				misc1->AddColor("menu color", &g_Settings.config.cMenuColor);
				misc1->AddText("menu color");
				misc1->AddCheckBox("watermark", &g_Settings.misc.bWatermark);
				misc1->AddButton("unhook", Detach);

			}

			auto gameSettings = tab3->AddSection("game settings", .844f);
			{
				gameSettings->AddText("event logs");
				gameSettings->AddMulti("flags", g_Settings.misc.bEventLogs, std::vector<std::string>{
					"damage",
					"harmed"
				});
				gameSettings->AddCheckBox("auto bhop", &g_Settings.misc.bBhopEnabled);
				gameSettings->AddCheckBox("auto strafer", &g_Settings.misc.bAutoStrafer);
			}

			auto config = tab3->AddSection("configs", 1.2435f);
			{
				config->AddText("configuration");
				config->AddCombo("config", &g_Settings.config.cfgNumber, std::vector<std::string> { "1", "2", "3", "4", "5", "6" });
				config->AddButton("save", Save);
				config->AddButton("load", Load);
			}

		}	mainWindow->AddChild(tab3);

		auto tab4 = std::make_shared<Tab>("E", 2, mainWindow);
		{
			auto config1 = tab4->AddSection("players", 1.2435f);
			{

			}

			auto config2 = tab4->AddSection("settings", 1.2435f);
			{

			}
		}	mainWindow->AddChild(tab4);

		auto tab5 = std::make_shared<Tab>("I", 2, mainWindow);
		{

		} mainWindow->AddChild(tab5);

    }
    this->vecChildren.push_back(mainWindow);



    /* Create our mouse cursor (one instance only) */
    mouseCursor = std::make_unique<MouseCursor>();

    /* Do the first init run through all of the objects */
	for (auto& it : vecChildren)
		it->Initialize();

}

