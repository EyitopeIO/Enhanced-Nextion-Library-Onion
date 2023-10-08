#include "Nextion.h"
#include "helpers.h"
#include "KnemesisAssets.h"
#include "Onion.h"


SoftwareSerial mySerial(DISPLAY_UART_PORT);
Nextion *next = Nextion::GetInstance(mySerial); // software serial

NexPage splash_screen(next, KnemesisPages::SPLASH_SCREEN, "page0");
NexPage scratch_pad(next, KnemesisPages::SCRATCH_PAD, "page1");
NexPage notification_page(next, KnemesisPages::NOTIFICATION_PAGE, "page2");
NexPage knemesis_home(next, KnemesisPages::KNEMESIS_HOME, "knemesis");

NexText title(next, KnemesisPages::SCRATCH_PAD, 1, "t0", &scratch_pad);
NexText scratch_pad_text(next, KnemesisPages::SCRATCH_PAD, 2, "t1", &scratch_pad);

NexPicture knemesis_wallpaper(next, KnemesisPages::KNEMESIS_HOME, 1, "p0", &knemesis_home);

NexTouch *nex_listen_list[] = {
  &splash_screen,
  &scratch_pad,
  &notification_page,
  &knemesis_home,
  &title,
  &scratch_pad_text,
  &knemesis_wallpaper,
  nullptr
};

#ifdef FLAVOUR_DEBUG
static void debug_callback(void *ptr)
{
  std::cerr << "register_debug_callback(): !!" << std::endl;
}
#endif

void nextion_thread_func(void)
{
    DEBUG_PRINT("nextion_events(): Starting nextion_events thread");
    while(1) next->nexLoop(nex_listen_list);
}

void initialize_nextion(void)
{
  delay(500); // arbitrary delay for display to startup
  next->nexInit(static_cast<unsigned int>(DISPLAY_UART_BAUD));
  next->sendCommand("vis 255,1");     // Show component on current page
  next->sendCommand("thsp=3");        // Sets internal No-touch-then-sleep timer to 3s
  next->sendCommand("thup=1");        // Sets if Nextion should auto-wake from sleep when touch press occurs to 30s
  next->sendCommand("ussp=30");       // Sets internal No-serial-then-sleep timer to 30s
  next->sendCommand("dims=10");       // Sets internal No-serial-then-sleep timer to 30s
#ifdef FLAVOUR_DEBUG
  splash_screen.attachPush(debug_callback);
  scratch_pad.attachPush(debug_callback);
  notification_page.attachPush(debug_callback);
  knemesis_home.attachPush(debug_callback);
  title.attachPush(debug_callback);
  scratch_pad_text.attachPush(debug_callback);
  knemesis_wallpaper.attachPush(debug_callback);
#endif
}
