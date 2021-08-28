#include <functional>
#include <Cocoa/Cocoa.h>
#include <libext/ui/app.hpp>

@interface __Delegate : NSObject<NSApplicationDelegate>

- (id)initWithOnRun:(std::function<void()>)onRun onExit:(std::function<void()>)onExit;

@end

@implementation __Delegate {
    std::function<void()> _onRun;
    std::function<void()> _onExit;
}

- (id)initWithOnRun:(std::function<void()>)onRun onExit:(std::function<void()>)onExit {
    self = [super init];
    if (self) {
        _onRun = onRun;
        _onExit = onExit;
    }
    return self;
}

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
    _onRun();
}

- (void)exit {
    _onExit();
}

@end

namespace ext::ui {

app::~app() {
    [[NSApplication sharedApplication] setDelegate: nil];
}

app::app(ext::ui::app_options const& options)
    : _events() {
    [[NSApplication sharedApplication]
        setDelegate: [[__Delegate alloc]
            initWithOnRun: [&, options](){
                id mainMenu = [[NSMenu alloc] init];
                id appMenu = [[NSMenu alloc] init];
                id appItem = [mainMenu addItemWithTitle: [NSString stringWithCString: "" encoding: NSUTF8StringEncoding] action: nil keyEquivalent: @""];
                id quitItem = [appMenu addItemWithTitle: @"Quit" action: nil keyEquivalent: @"q"];
                [quitItem setTarget: [NSApp delegate]];
                [quitItem setAction: @selector(exit)];
                [appItem setSubmenu: appMenu];
                [NSApp setMainMenu: mainMenu];
                [NSApp setActivationPolicy: NSApplicationActivationPolicyRegular];
                [appMenu setTitle: [NSString stringWithCString: options.title.c_string() encoding: NSUTF8StringEncoding]];
            }
            onExit: [&](){
                _events.push(
                    ext::ui::event::basic_event(
                        ext::ui::event_type::exit
                    )
                );
            }
        ]
    ];
    [NSApp finishLaunching];
}

void app::process(ext::ui::app_process_options const& options) {
    NSEvent* event = [NSApp nextEventMatchingMask: NSEventMaskAny
                                        untilDate: [NSDate dateWithTimeIntervalSinceNow: options.timeout]
                                            inMode: NSDefaultRunLoopMode
                                            dequeue: YES];
    if (event != nil) {
        [NSApp sendEvent: event];
        [NSApp updateWindows];
    }
}

} /* namespace ext::ui */