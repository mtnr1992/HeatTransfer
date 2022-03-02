#include <analysis.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "HeatTransfer_1.h"

static int panelHandle,panelHandle2 ;

typedef struct
{
	 double mass;
	 double capacity;
	 double T;
}body;

body bodies[3];



double cond,I1, I2, dQ1, dQ2, TL, TR, dt=0.01, timedisplay=0, x, y;
int counter=0,i=0;  

double time_arr[10000], TL_arr[10000],TR_arr[10000];


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "HeatTransfer_1.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 = LoadPanel (0, "HeatTransfer_1.uir", PANEL_2)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	DiscardPanel (panelHandle2);
	return 0;
}

int CVICALLBACK ExitFunc (int panel, int event, void *callbackData,
						  int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
int CVICALLBACK MaterialRing (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panelHandle,PANEL_MATRING,&cond);
			SetCtrlVal(panelHandle,PANEL_COND,cond);
			
			if(cond==205.0)//aluminum
				SetCtrlVal(panelHandle,PANEL_PICMATRING,"ALUMINUM");
			if(cond==314.0)//gold
				SetCtrlVal(panelHandle,PANEL_PICMATRING,"GOLD");
			if(cond==0.12)//wood
				SetCtrlVal(panelHandle,PANEL_PICMATRING,"WOOD");
			if(cond==109.0)//brass
				SetCtrlVal(panelHandle,PANEL_PICMATRING,"BRASS"); 
			if(cond==1.6)//ice
				SetCtrlVal(panelHandle,PANEL_PICMATRING,"ICE"); 
			if(cond==1.0)//null
				SetCtrlVal(panelHandle,PANEL_PICMATRING,"NULL"); 
			
			
			break;
	}
	return 0;
}

int CVICALLBACK StartStop (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			
			//get temp
			GetCtrlVal(panelHandle,PANEL_LeftTemperature,&bodies[1].T);  
			GetCtrlVal(panelHandle,PANEL_RightTemperature,&bodies[2].T);
			//get mass
			GetCtrlVal(panelHandle,PANEL_MassLeft,&bodies[1].mass);
			GetCtrlVal(panelHandle,PANEL_MassRight,&bodies[2].mass);
			//get capacity
			GetCtrlVal(panelHandle,PANEL_CapacityLeft,&bodies[1].capacity);
			GetCtrlVal(panelHandle,PANEL_CapacityRight,&bodies[2].capacity);
			//get cond 
			GetCtrlVal(panelHandle,PANEL_COND,&cond);
			
			TL=bodies[1].T;
			TR=bodies[2].T;
			
			i++;
			
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, i%2);// start stop 
			
			if(i%2 ){
			counter=0;
			timedisplay=0;
			
			}
			break;
	}
	return 0;
}

int CVICALLBACK Time (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			//clock display
			timedisplay++;
			SetCtrlVal(panelHandle,PANEL_DT,timedisplay/100); 
			
			if( fabs(TL-TR)<0.001 ){	
			SetCtrlVal (panelHandle, PANEL_TOGGLEBUTTON,0);//switch
			timedisplay=0;
			i++;
			SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);// stop	
			
			}
			
			I1=cond*(TL-TR);
			I2=-I1;
			
			dQ1=I1* dt;
			dQ2=I2* dt; 
			
			TL=TL - dQ1/(bodies[1].mass* bodies[1].capacity) ;
			TR=TR - dQ2/(bodies[2].mass* bodies[2].capacity) ;
			
			//plot data
			TL_arr[counter] =TL;
			TR_arr[counter] =TR;
			time_arr[counter]=counter*dt; 	
			counter++; 
			
			
			//set color
			SetCtrlAttribute (panelHandle, PANEL_BODYLEFT, ATTR_FRAME_COLOR, MakeColor(TL*(255/200) ,0,0));
			SetCtrlAttribute (panelHandle, PANEL_BODYRIGHT, ATTR_FRAME_COLOR, MakeColor(TR*(255/200) ,0,0));
			
			SetCtrlAttribute (panelHandle, PANEL_LeftTemperature, ATTR_FILL_COLOR, MakeColor(TL*(255/200) ,0,0));
			SetCtrlAttribute (panelHandle, PANEL_RightTemperature, ATTR_FILL_COLOR, MakeColor(TR*(255/200) ,0,0));
			//set numeric
			SetCtrlVal(panelHandle,PANEL_LeftTemperature,TL);
			SetCtrlVal(panelHandle,PANEL_RightTemperature,TR);
			
				
				
				
			break;
	}
	return 0;
}

int CVICALLBACK SlideTempLeft (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(panelHandle,PANEL_LeftTemperature,&bodies[1].T);
			TL=bodies[1].T; 
			SetCtrlAttribute (panelHandle, PANEL_BODYLEFT, ATTR_FRAME_COLOR, MakeColor(TL*255/200 ,0,0));
			SetCtrlAttribute (panelHandle, PANEL_LeftTemperature, ATTR_FILL_COLOR, MakeColor(TL*255/200 ,0,0));
			
			break;
	}
	return 0;
}

int CVICALLBACK SlideTempRight (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlVal(panelHandle,PANEL_RightTemperature,&bodies[2].T);
			TR=bodies[2].T;
			SetCtrlAttribute (panelHandle, PANEL_BODYRIGHT, ATTR_FRAME_COLOR, MakeColor(TR*255/200 ,0,0)); 
			SetCtrlAttribute (panelHandle, PANEL_RightTemperature, ATTR_FILL_COLOR, MakeColor(TR*255/200 ,0,0));  
			
			break;
	}
	return 0;
}

int CVICALLBACK ExitFunc2 (int panel, int event, void *callbackData,
						   int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			HidePanel(panelHandle2);
			break;
	}
	return 0;
}

int CVICALLBACK Help (int panel, int control, int event,
					  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				MessagePopup("HELP", "Enter for each body Mass & Capacity values, and intially temrepature \nPress Start and wait for stabilization or press Stop\nThen press GRAPH");
			break;
	}
	return 0;
}

int CVICALLBACK OpenPanel (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DisplayPanel (panelHandle2);
			break;
	}
	return 0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int CVICALLBACK GraphCtrl (int panel, int control, int event,//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PANEL 2
						   void *callbackData, int eventData1, int eventData2)
{
  static double Delta_arr[10000],Log_arr[10000],LinFit_arr[10000],slope,intercept,meas, trueslope ;
static int ring	;				
 //--------------------------------------------------------------------------------- delta & log creating
 for(int j=0;j<counter;j++){
	Delta_arr[j]=fabs(TL_arr[j]-TR_arr[j]); 
	Log_arr[j]=log (Delta_arr[j]);
 }
					
  switch (event)
	{
		case EVENT_COMMIT:
			 switch(control)
			 {
				case PANEL_2_PLOT:
					if(counter){
					   GetCtrlVal(panelHandle2,PANEL_2_RING, &ring);
					   switch(ring){
						   case 1:  //----------------------------------------------PLOT left body
									PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, TL_arr, counter,
											VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED);
								
									
								break;
								
						   case 2:  //----------------------------------------------PLOT right body
									PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, TR_arr, counter,
											VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_GREEN);
								break;

						   case 3:   //--------------------------------------------PLOT delta temp
									PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, Delta_arr, counter,
											VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_BLUE);
								break;
								
						   case 4:  //----------------------------------------------PLOT log delta
									PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, Log_arr, counter,
											VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_BLACK);
									SetCtrlAttribute (panelHandle2, PANEL_2_LINFIT, ATTR_DIMMED, 0);
								break;	   
					   } }
				else MessagePopup("No Data to Display","You need to performe test ");	
				break;
					 
				case PANEL_2_CLEAR:
					
					DeleteGraphPlot (panelHandle2, PANEL_2_GRAPH, -1, VAL_IMMEDIATE_DRAW);
					
					break;
					 
				case PANEL_2_LINFIT:  
						  
						  LinFit (time_arr, Log_arr, counter, LinFit_arr,&slope,&intercept,&meas);
						  
						  PlotXY (panelHandle2, PANEL_2_GRAPH, time_arr, LinFit_arr, counter,
											VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE,
											VAL_EMPTY_SQUARE, VAL_SOLID, 1, MakeColor(255,0,255));
						  // -----------------------------------------------------------------------------true slope  calc
						  trueslope=-cond*(bodies[1].mass*bodies[1].capacity+bodies[2].mass*bodies[2].capacity)/ 
									(bodies[1].mass*bodies[1].capacity*bodies[2].mass*bodies[2].capacity);
						  // -----------------------------------------------------------------------------linfit parameters update  
						  SetCtrlVal(panelHandle2,PANEL_2_TrueSlope,trueslope);			  
						  SetCtrlVal(panelHandle2,PANEL_2_Slope,slope);
						  SetCtrlVal(panelHandle2,PANEL_2_Intercept,intercept);
						  SetCtrlVal(panelHandle2,PANEL_2_Error,meas);
					break;
			 }
			break;
	}
	return 0;
}

int CVICALLBACK GraphCursor (int panel, int control, int event,//-------------------------------------------CURSOR CONTROL
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetGraphCursor (panelHandle2, PANEL_2_GRAPH, 1, &x, &y);
			SetCtrlVal(panelHandle2,PANEL_2_CursorTime,x);
			SetCtrlVal(panelHandle2,PANEL_2_CursorValue,y);
			break;
	}
	return 0;
}



