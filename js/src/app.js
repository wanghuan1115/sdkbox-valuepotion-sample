
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.
        // ask the window size
        var size = cc.winSize;

        /////////////////////////////
        // 3. add your codes below...
        // add a label shows "Hello World"
        // create and initialize a label
        var helloLabel = new cc.LabelTTF("Hello World", "Arial", 38);
        // position the label on the center of the screen
        helloLabel.x = size.width / 2;
        helloLabel.y = size.height / 2 + 200;
        // add the label as a child to this layer
        this.addChild(helloLabel, 5);

        var item1 = new cc.MenuItemFont("Show Ad", this.onButtonClicked, this);

        var menu = new cc.Menu(item1);
        menu.x = size.width/2
        menu.y = size.height/2;
        menu.alignItemsVerticallyWithPadding(20);
        this.addChild(menu)

        //init sdk
        var plugin = sdkbox.PluginValuePotion
        plugin.setListener({
            onCacheInterstitial: function(placement) { cc.log("onCacheInterstitial ") },
            onFailToCacheInterstitial: function(placement, errorMessage) { cc.log("onFailToCacheInterstitial ") },
            onOpenInterstitial: function(placement) { cc.log("onOpenInterstitial ") },
            onFailToOpenInterstitial: function(placement, errorMessage) { cc.log("onFailToOpenInterstitial ") },
            onCloseInterstitial: function(placement) { cc.log("onCloseInterstitial ") },
            onRequestOpenURL: function(placement, URL) { cc.log("onRequestOpenURL ") },
            onRequestPurchase: function(placement, name, productId, quantity, campaignId, contentId) {
                cc.log("onRequestPurchase ");
            },
            onRequestRewards: function(placement, rewards) {
                cc.log("onRequestRewards ");
                for (var i = rewards.length - 1; i >= 0; i--) {
                    var r = rewards[i]
                    cc.log("%d name:%s, q:%d", i, r.name, r.quantity)
                };

            }
        })
        plugin.init()

        plugin.setTest(true)
        if (!plugin.hasCachedInterstitial("default")) {
            plugin.cacheInterstitial("default")
        }

        plugin.trackEvent("test event")
        plugin.trackEvent("test event with value 23", 23)
        plugin.trackEvent("category", "event name", "label", 45)

        plugin.trackPurchaseEvent("test event", 56, "RMB", "order id", "product id")
        plugin.trackPurchaseEvent("test event", 67, "USD", "order id", "product id", "campaign id", "content id")
        plugin.trackPurchaseEvent("categroy", "event name", "label", 78, "ILY", "order id", "product id", "campaign id", "content id");

        plugin.userinfo("id", "user id")
        plugin.userinfo("serverid", "server id")
        plugin.userinfo("birth", "19991111")  //YYYYMMDD
        plugin.userinfo("gender", "M")
        plugin.userinfo("level", "9")
        plugin.userinfo("friends", "3")
        plugin.userinfo("accounttype", "facebook")

        return true;
    },
    onButtonClicked: function() {
        var plugin = sdkbox.PluginValuePotion
        plugin.openInterstitial("default")
    },
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

