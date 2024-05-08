//#define LGFX_AUTODETECT
#include <LovyanGFX.hpp>
#include "lgfx_ESP32_2432S028R_ST7789.h"
//#include "u8g2_font_d9cdf0b9c03077b23adf863d88ecaa0c.h"

//LGFX lcd;
LGFX_Sprite canvas;

static constexpr char text[] = "Hello world ! ęóąśłżźćńĘÓĄŚŁŻŹĆŃ1234567890 this is long long string sample ę . Ą";
static constexpr size_t textlen = sizeof(text) / sizeof(text[0]);
size_t textpos = 0;

void setup(void) 
{
  tft.init();

  // 画面が横長になるように回転
  if (tft.width() < tft.height()) tft.setRotation(tft.getRotation() ^ 1);

  canvas.setColorDepth(8);
  canvas.setFont(&fonts::lgfxJapanMinchoP_32);

  //canvas.setFont(u8g2_font_unifont_myfonts);
  canvas.setTextWrap(false);        // 右端到達時のカーソル折り返しを禁止
  canvas.createSprite(tft.width() + 36, 36); // 画面幅+１文字分の横幅を用意
}

void loop(void)
{
  int32_t cursor_x = canvas.getCursorX() - 1;   // 現在のカーソル位置を取得し、1ドット左に移動
  if (cursor_x <= 0) // カーソル位置が左端に到達している場合は一周したと判断
  {
    textpos = 0;            // 文字列の読取り位置をリセット
    cursor_x = tft.width(); // 新たな文字が画面右端に描画されるようにカーソル位置を変更
  }

  canvas.setCursor(cursor_x, 0); // カーソル位置を更新
  canvas.scroll(-1, 0);          // キャンバスの内容を1ドット左にスクロール
  while (textpos < textlen && cursor_x <= tft.width()) // 画面右端に文字が書けるか判定
  {
    canvas.print(text[textpos++]);   // 1バイトずつ出力 (マルチバイト文字でもこの処理で動作します)
    cursor_x = canvas.getCursorX();  // 出力後のカーソル位置を取得
  }

  canvas.pushSprite(&tft, 0, 0);
}
