/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: ExitFunc */
#define  PANEL_BODYLEFT                   2       /* control type: deco, callback function: (none) */
#define  PANEL_TOGGLEBUTTON               3       /* control type: textButton, callback function: StartStop */
#define  PANEL_MassRight                  4       /* control type: numeric, callback function: (none) */
#define  PANEL_CapacityRight              5       /* control type: numeric, callback function: (none) */
#define  PANEL_MassLeft                   6       /* control type: numeric, callback function: (none) */
#define  PANEL_CapacityLeft               7       /* control type: numeric, callback function: (none) */
#define  PANEL_COND                       8       /* control type: numeric, callback function: (none) */
#define  PANEL_LeftTemperature            9       /* control type: scale, callback function: SlideTempLeft */
#define  PANEL_RightTemperature           10      /* control type: scale, callback function: SlideTempRight */
#define  PANEL_BODYRIGHT                  11      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG                    12      /* control type: textMsg, callback function: (none) */
#define  PANEL_TEXTMSG_2                  13      /* control type: textMsg, callback function: (none) */
#define  PANEL_TIMER                      14      /* control type: timer, callback function: Time */
#define  PANEL_DT                         15      /* control type: numeric, callback function: (none) */
#define  PANEL_COMMANDBUTTON              16      /* control type: command, callback function: OpenPanel */
#define  PANEL_MATRING                    17      /* control type: ring, callback function: MaterialRing */
#define  PANEL_DECORATION                 18      /* control type: deco, callback function: (none) */
#define  PANEL_HELP                       19      /* control type: command, callback function: Help */
#define  PANEL_PICMATRING                 20      /* control type: pictRing, callback function: (none) */

#define  PANEL_2                          2       /* callback function: ExitFunc2 */
#define  PANEL_2_GRAPH                    2       /* control type: graph, callback function: GraphCursor */
#define  PANEL_2_LINFIT                   3       /* control type: command, callback function: GraphCtrl */
#define  PANEL_2_CLEAR                    4       /* control type: command, callback function: GraphCtrl */
#define  PANEL_2_PLOT                     5       /* control type: command, callback function: GraphCtrl */
#define  PANEL_2_RING                     6       /* control type: ring, callback function: (none) */
#define  PANEL_2_Error                    7       /* control type: numeric, callback function: (none) */
#define  PANEL_2_Intercept                8       /* control type: numeric, callback function: (none) */
#define  PANEL_2_Slope                    9       /* control type: numeric, callback function: (none) */
#define  PANEL_2_TrueSlope                10      /* control type: numeric, callback function: (none) */
#define  PANEL_2_CursorValue              11      /* control type: numeric, callback function: (none) */
#define  PANEL_2_CursorTime               12      /* control type: numeric, callback function: (none) */
#define  PANEL_2_TEXTMSG                  13      /* control type: textMsg, callback function: (none) */
#define  PANEL_2_DECORATION_2             14      /* control type: deco, callback function: (none) */
#define  PANEL_2_DECORATION               15      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ExitFunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ExitFunc2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphCursor(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Help(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MaterialRing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OpenPanel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SlideTempLeft(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SlideTempRight(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartStop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Time(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
