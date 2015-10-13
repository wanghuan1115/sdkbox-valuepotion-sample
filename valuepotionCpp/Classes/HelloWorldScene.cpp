#include "HelloWorldScene.h"
#include "PluginValuePotion/PluginValuePotion.h"

USING_NS_CC;

static const char* placement = "default";

class VPListener : public sdkbox::ValuePotionListener {
public:
    virtual void onCacheInterstitial(const char *placement) {
        CCLOG("VP onCacheInterstitial:%s", placement);
    }

    virtual void onFailToCacheInterstitial(const char *placement, const char *errorMessage) {
        CCLOG("VP onFailToCacheInterstitial:%s error:%s", placement, errorMessage);
    }

    virtual void onOpenInterstitial(const char *placement) {
        CCLOG("VP onOpenInterstitial:%s", placement);
    }

    virtual void onFailToOpenInterstitial(const char *placement, const char *errorMessage) {
        CCLOG("VP onFailToOpenInterstitial:%s error:%s", placement, errorMessage);
    }

    virtual void onCloseInterstitial(const char *placement) {
        CCLOG("VP onCloseInterstitial:%s", placement);
    }

    virtual void onRequestOpenURL(const char *placement, const char *URL) {
        CCLOG("VP onRequestOpenURL:%s url:%s", placement, URL);
    }

    virtual void onRequestPurchase(const char *placement, const char *name, const char *productId, int quantity, const char *campaignId, const char *contentId) {
        CCLOG("VP onRequestPurchase:%s, name:%s, productId:%s, quantity:%d, campaignId:%s, contentId:%s",
            placement, name, productId, quantity, campaignId, contentId);
    }

    virtual void onRequestRewards(const char *placement, std::vector<sdkbox::ValuePotionReward> rewards) {
        CCLOG("VP onRequestRewards:%s\n", placement);
        int i = 0;
        for (auto r : rewards) {
            CCLOG("%d name:%s, quantity:%d\n", i, r.name.c_str(), r.quantity);
            i++;
        }
    }

};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("VP Sample", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    
    Menu* list = Menu::create(
                              MenuItemFont::create("Show Ad", CC_CALLBACK_1(HelloWorld::onButton1Click, this)),
                              NULL);
    list->alignItemsVerticallyWithPadding(5);
    list->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    addChild(list);
	
    sdkbox::PluginValuePotion::setListener(new VPListener());
    sdkbox::PluginValuePotion::init();

    sdkbox::PluginValuePotion::setTest(true);
    if (!sdkbox::PluginValuePotion::hasCachedInterstitial(placement)) {
        sdkbox::PluginValuePotion::cacheInterstitial(placement);
    }

    sdkbox::PluginValuePotion::trackEvent("test event");
    sdkbox::PluginValuePotion::trackEvent("test event with value 23", 23);
    sdkbox::PluginValuePotion::trackEvent("category", "event name", "label", 45);

    sdkbox::PluginValuePotion::trackPurchaseEvent("test event", 56, "RMB", "order id", "product id");
    sdkbox::PluginValuePotion::trackPurchaseEvent("test event", 67, "USD", "order id", "product id", "campaign id", "content id");
    sdkbox::PluginValuePotion::trackPurchaseEvent("categroy", "event name", "label", 78, "ILY", "order id", "product id", "campaign id", "content id");

    sdkbox::PluginValuePotion::userinfo("id", "user id");
    sdkbox::PluginValuePotion::userinfo("serverid", "server id");
    sdkbox::PluginValuePotion::userinfo("birth", "birther day");
    sdkbox::PluginValuePotion::userinfo("genDer", "Male");
    sdkbox::PluginValuePotion::userinfo("level", "9");
    sdkbox::PluginValuePotion::userinfo("friends", "3");
    sdkbox::PluginValuePotion::userinfo("accounttype", "account type");

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onButton1Click(Ref *sender)
{
    sdkbox::PluginValuePotion::openInterstitial(placement);
    CCLOG("Button1 Click");
}

