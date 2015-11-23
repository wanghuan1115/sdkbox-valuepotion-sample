
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    -- add HelloWorld label
    cc.Label:createWithSystemFont("Hello World", "Arial", 40)
        :move(display.cx, display.cy + 200)
        :addTo(self)

    cc.Menu:create(
        cc.MenuItemFont:create("Show Ad"):onClicked(function() self:onButtonClicked() end))
            :move(display.cx, display.cy)
            :alignItemsVerticallyWithPadding(5)
            :addTo(self)

    self:initSDK()
end

function MainScene:initSDK()
    local plugin = sdkbox.PluginValuePotion
    plugin:setListener(function(args)
        local event = args.event
        dump(args, "value potion listener info:")
    end)
    plugin:init()

    plugin:setTest(true)
    if not plugin:hasCachedInterstitial("default") then
        plugin:cacheInterstitial("default")
    end

    plugin:trackEvent("test event")
    plugin:trackEvent("test event with value 23", 23)
    plugin:trackEvent("category", "event name", "label", 45)

    plugin:trackPurchaseEvent("test event", 56, "RMB", "order id", "product id")
    plugin:trackPurchaseEvent("test event", 67, "USD", "order id", "product id", "campaign id", "content id")
    plugin:trackPurchaseEvent("categroy", "event name", "label", 78, "ILY", "order id", "product id", "campaign id", "content id");

    plugin:userinfo("id", "user id")
    plugin:userinfo("serverid", "server id")
    plugin:userinfo("birth", "19991111") --YYYYMMDD
    plugin:userinfo("gender", "M")
    plugin:userinfo("level", "9")
    plugin:userinfo("friends", "3")
    plugin:userinfo("accounttype", "facebook")
end

function MainScene:onButtonClicked()
    local plugin = sdkbox.PluginValuePotion
    plugin:openInterstitial("default")
end

return MainScene
