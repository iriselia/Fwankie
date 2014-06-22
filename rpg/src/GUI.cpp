#include "Precompiled.h"
#include "GUI.h"
#include "Base/Main.h"
#include "vld.h"

	void notifyMouseSetFocus(MyGUI::Widget* _sender, MyGUI::Widget* _old)
	{
		MyGUI::ImageBox* image = _sender->castType<MyGUI::ImageBox>();
		image->setItemName("Active");
	}

	void notifyMouseLostFocus(MyGUI::Widget* _sender, MyGUI::Widget* _new)
	{
		MyGUI::ImageBox* image = _sender->castType<MyGUI::ImageBox>();
		image->setItemName("Normal");
	}

	void GUI::setupResources()
	{
		base::BaseManager::setupResources();
		addResourceLocation(getRootMedia() + "/Demos/Demo_Picking");
		addResourceLocation(getRootMedia() + "/Common/Demos");
	}

	void GUI::createScene()
	{
		const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("HelpPanel.layout");
		root.at(0)->findWidget("Text")->castType<MyGUI::TextBox>()->setCaption("Sample of picking mask for widget.");


		//MyGUI::VectorWidgetPtr& wallpaper = MyGUI::LayoutManager::getInstance().loadLayout("Wallpaper.layout");
		/*
		const MyGUI::VectorWidgetPtr& root = MyGUI::LayoutManager::getInstance().loadLayout("HelpPanel.layout");
		root.at(0)->findWidget("Text")->castType<MyGUI::TextBox>()->setCaption("Sample of picking mask for widget.");

		MyGUI::ResourceManager::getInstance().load("Resources.xml");

		const MyGUI::IntSize& view = MyGUI::RenderManager::getInstance().getViewSize();
		const MyGUI::IntSize size(128, 128);

		MyGUI::ImageBox* image = MyGUI::Gui::getInstance().createWidget<MyGUI::ImageBox>("ImageBox", MyGUI::IntCoord((view.width - size.width) / 2, (view.height - size.height) / 2, size.width, size.height), MyGUI::Align::Default, "Main");
		image->setItemResource("pic_Crystal_Clear_Butterfly");
		image->setItemGroup("States");
		image->setItemName("Normal");

		image->eventMouseSetFocus += MyGUI::newDelegate(notifyMouseSetFocus);
		image->eventMouseLostFocus += MyGUI::newDelegate(notifyMouseLostFocus);

		image->setMaskPick("Crystal_Clear_Butterfly_Pick.png");
		//*/
		//MyGUI::LayoutManager::getInstance().unloadLayout(wallpaper);
	}

	void GUI::destroyScene()
	{
	}

//MYGUI_APP(demo::DemoKeeper)
