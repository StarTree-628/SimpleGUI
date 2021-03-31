#ifndef _INCLUDE_SIMPLE_GUI_CONFIG_H_
#define _INCLUDE_SIMPLE_GUI_CONFIG_H_

//=======================================================================//
//= Used for SimpleGUI features.									    =//
//=======================================================================//
#define SGUI_CONF_DEBUG_ERROR   0
#define SGUI_CONF_DEBUG_WARN    1

#define SGUI_CONF_DEBUG_LEVEL    SGUI_CONF_DEBUG_ERROR                       
/**
 * Wheather to try mapping colors in different gray scale depth bits.
 *      0 means disable color mapping
 *      1 means enable color mapping
 *      defualt: 0
 * The SimpleGUI would try to mapping pixels with different color space into
 * screen's color space. If you decide to disable this feafure for more performance,
 * you should ensure the pixels' color space is same as screen's color space,
 * otherwise there will be overflow issues. This option would be set to 0 forcely
 * when SGUI_CONF_GRAYSCALE_DEPTH_BITS is set to 1.
 * e.g. You have a screen with 4bits grayscale and pixels with 1bit grayscale.
 *      You tried to draw the 1bit pixels into the 4bits screen. If the macro
 *      is set to 1, the SimpleGUI will mapping the pixels with 0x00 into
 *      0x00 and the pixels with 0x01 into 0x0F and make sure the display is
 *      well; If the option is set to 0, the SimpleGUI will not do anything
 *      color mapping and draw pixels into the screen directly.
 */
#define SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED       1
/**
 * Wheather to use Alpha mix in font render (Unavailable)
 *
 * This is important for gray scale screens. If you turn on this option,
 * the SimpleGUI will treat character bitmaps as the alpha channel and try
 * to mix it with existed pixels. If you turn off this option, the SimpleGUI
 * will treat character bitmaps as the final pixel and draw the bitmap directy,
 * which would lead to a strage black background when draw characters onto a
 * non-black background in gray scale screens.
 */
#define SGUI_CONF_FONT_USE_ALPHA_MIX                    1
/**
 * The maximum number of gray scale bits that SimpleGUI is compatibled with
 * when color mapping is ENABLED and the global number of gray scale bits
 * when color mapping is DISABLED.
 * default: 0
 */
#define SGUI_CONF_GRAYSCALE_DEPTH_BITS                  4
/**
 * The prepared buffer for transfer bitmap data. This buffer would be used
 * if you decide to load bitmap data (e.g. bitmap,fonts) from external
 * storage. The buffer can be disabled by setting this macro to 0, in this
 * case you will get a null pointer in fnGetPixmap of SGUI_FONT_RES and
 * need to prepare buffers your-self when loading bitmaps. If you only use
 * internal font resource, setting this options to zero for saving RAM is
 * recomended.
 */
#define	SGUI_CONF_BMP_DATA_BUFFER_SIZE				(512)
#define	SGUI_NUMBER_STR_LENGTH_MAX		            (12)
//=======================================================================//
//= Used for SimpleGUI virtual SDK.									    =//
//=======================================================================//
#ifdef _SIMPLE_GUI_ENCODE_TEXT_
 #define _SIMPLE_GUI_ENCODE_TEXT_SRC_		("UTF-8")
 #define _SIMPLE_GUI_ENCODE_TEXT_DEST_		("GB2312")
#endif // _SIMPLE_GUI_ENCODE_TEXT_
//#define _SIMPLE_GUI_IN_VIRTUAL_SDK_

//=======================================================================//
//= Used for SimpleGUI interface.									    =//
//=======================================================================//
//#define _SIMPLE_GUI_ENABLE_DYNAMIC_MEMORY_

//=======================================================================//
//= Process Macro definitions.										    =//
//= DO NOT MODIFY FOLLOWING LINES!                                      =//
//=======================================================================//

// set Color mapping default value
#ifndef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    #define SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED 0
#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED

// Simplify COLOR_MAPPING Macros
#if SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED==0
    #undef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
#elif SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED==1
    #undef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    #define SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
#else
    #error Unresolved SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED value, please make sure its value is 0 or 1.
#endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED

// set FONT_ALPHA_MIX default value
#ifndef SGUI_CONF_FONT_USE_ALPHA_MIX
    #define SGUI_CONF_FONT_USE_ALPHA_MIX 0
#endif // SGUI_CONF_FONT_USE_ALPHA_MIX

// Simplify SGUI_CONF_FONT_USE_ALPHA_MIX
#if SGUI_CONF_FONT_USE_ALPHA_MIX==0
    #undef SGUI_CONF_FONT_USE_ALPHA_MIX
#elif SGUI_CONF_FONT_USE_ALPHA_MIX==1
    #undef SGUI_CONF_FONT_USE_ALPHA_MIX
    #define SGUI_CONF_FONT_USE_ALPHA_MIX
#else
    #error Unresolved SGUI_CONF_FONT_USE_ALPHA_MIX value.
#endif // SGUI_CONF_FONT_USE_ALPHA_MIX

// set MAX_DEPTH_BITS default value
#ifndef SGUI_CONF_GRAYSCALE_DEPTH_BITS
    #define SGUI_CONF_GRAYSCALE_MAX_DEPTH_BITS 1
#elif SGUI_CONF_GRAYSCALE_DEPTH_BITS < 0
    #error SGUI_CONF_GRAYSCALE_DEPTH_BITS cannot be negative.
#endif // SGUI_CONF_GRAYSCALE_DEPTH_BITS

// check the MAX_DEPTH_BITS and turn off the unnecessary features
#if SGUI_CONF_GRAYSCALE_DEPTH_BITS==1
    // disable COLOR_MAPPING
    #ifdef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
        #undef SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    #endif // SGUI_CONF_GRAYSCALE_COLOR_MAPPING_ENABLED
    // disable Alpha Mix
    #ifdef SGUI_CONF_FONT_USE_ALPHA_MIX
        #undef SGUI_CONF_FONT_USE_ALPHA_MIX
    #endif // SGUI_CONF_FONT_USE_ALPHA_MIX
#endif // SGUI_CONF_GRAYSCALE_DEPTH_BITS

#endif // _INCLUDE_SIMPLE_GUI_CONFIG_H_
