/*****************************************************************
 * Filename   | Example_Programs.cpp
 * Author     | Scott J. Schneider 
 *
 * Assignment | Programming Exercise for ECT362
 * Due date   | 01/01/07
 *****************************************************************/

/*****************************************************************
 * Problem Statement | 
 *
 * Inputs            | 
 * Outputs           | 
 * Processes         | 
 * 
 * Pseudocode Design | 1.
 *                   | 2. 
 *                   | 3. 
 *                   | 4. 
 ******************************************************************/

/* Preprocessor Directives */
#include <windows.h>  // Win32 API
#include "resource.h"  // resources for your application

/* Function Prototypes */
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );  //the window procedure
/* A callback function is passed (by reference) to another function */

/* Global variables */

/* Functions */
/*****************************************************************
 * Function    | WinMain()
 * Description | Entry point for our application, we create and 
 *             |  register a window class and then call CreateWindow
 * Inputs      | None
 * Output      | Integer value 0
 *****************************************************************/ 
int WINAPI WinMain( HINSTANCE hInstance, 
				    HINSTANCE hPrevInstance,
                    LPSTR szCmdLine, 
					int iCmdShow ) 
{
    static char szAppName[] = "My Window";
	
	HWND        hwnd, lhWnd;
    WNDCLASSEX  wndclass;  // This is our new windows class
	MSG msg;

	/*  Fill in WNDCLASSEX struct members  */
    wndclass.cbSize         = sizeof(wndclass);
    wndclass.style          = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc    = WndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.hInstance      = hInstance;
    wndclass.hIcon = LoadIcon( GetModuleHandle(NULL),
MAKEINTRESOURCE(IDI_MYICON));
   wndclass.hIconSm = (HICON)LoadImage( GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON),
IMAGE_ICON, 16, 16, 0);                                             //(HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszClassName  = szAppName;
    wndclass.lpszMenuName   = NULL;

    /*  Register a new window class with Windows  */
    RegisterClassEx(&wndclass);

    /*  Create a window based on our new class  */
    hwnd = CreateWindow(szAppName,  // class name the window is to be based on 
						"My 1st Window",  // the title of the window that will 
						                  //  appear in the bar at the top
						WS_OVERLAPPEDWINDOW,  // window style (a window that 
						                      //  has a caption, a system menu, 
											  //  a thick frame and a minimise 
											  //  and maximise box)
						/* Use default starting location for window */
						CW_USEDEFAULT, // initial x position (top left corner)
						CW_USEDEFAULT, // initial y position (top left corner)
						440, // initial width
						220, // initial height
						NULL, // window parent (NULL for not a child window)
						NULL, // menu (NULL to use class menu)
						hInstance, // the program instance passed to us
						NULL);  // pointer to any parameters wished to be 
	                            //  passed to the window producer when the window
	                            //  is created
 
	if(hwnd == NULL)  // check to see if an error occurred in creating the window
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    /* Show and update our window  */
    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

 
	/*  Retrieve and process any queued messages until we get WM_QUIT  */
	/* Recall that Windows uses a messaging system to notify window of */
	/*  user actions												   */
    while ( GetMessage(&msg, NULL, 0, 0) ) 
	{
		TranslateMessage(&msg);  // for certain keyboard messages 
		DispatchMessage(&msg);  // send message to WndProc
    } 

    /*  Exit with status specified in WM_QUIT message  */
    return msg.wParam;
} // end WinMain()


/*****************************************************************
 * Function    | WinProc()
 * Description | Whenever anything happens to your window, Windows 
 *             |  will call this function telling you what has happened. 
 *             |  The message parameter contains the message sent
 * Inputs      | None
 * Output      | Integer value 0
 *****************************************************************/ 
LRESULT CALLBACK WndProc( HWND hwnd, 
						  UINT iMsg, 
						  WPARAM wParam, 
						  LPARAM lParam ) 
{
    PAINTSTRUCT ps;
	HDC hdc;

	/*  Switch according to what type of message we have received  */
	
	static HWND addbutton;

    switch ( iMsg ) 
	{
		case WM_PAINT:
		/* We receive WM_PAINT every time window is updated  */
			hdc = BeginPaint(hwnd, &ps);
			TextOut(hdc, 10, 160, "My First Window", 15);
			EndPaint(hwnd, &ps);
			break;
		case WM_CREATE:
        /* Operations to be performed when this window is created */ 
			addbutton = CreateWindow( "BUTTON",
								"ADD",
								WS_VISIABLE | WS_CHILD | BS_PUSHBUTTON,
								10,
								10,
								100,
								30,
								hwnd,
								(HMENU)ID_ADDBUTTON,
								(HINSTANCE) 0,
								NULL);
			break;
		case WM_DESTROY:
		/* Window has been destroyed, so exit cleanly  */
			PostQuitMessage(0);
			break;
		case WM_COMMAND:

			if (HIWORD(wParam) == BN_CLICKED)
			{
				switch (LOWORD(wParam))
				{
				case ID_ADDBUTTON:
					MessageBox(NULL, "Add Button Pressed", "ADD",
								MB_ICONINFORMATION | MB_OK);
 	    /* User selected a command from a menu or a control sent a message */
			break;
		default:
        /* We do not want to handle this message so pass back to Windows */
        /*  to handle it in a default way                                */
			return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}
	return 0;

} // end WndProc
