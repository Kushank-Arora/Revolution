#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>

#define TOP 50
#define SIDE 50
#define LEN 500
#define CEN (LEN/sqrt(2) + SIDE)

/* User Defined functions */

void OnTimer(HWND);
void OnCreate(HWND);


/* User defined stuff */

typedef enum fac{
    f1,f2,f3,f4
} face;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           844,                 /* The programs width */
           675,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_CREATE:
            OnCreate(hwnd);
            break;
        case WM_TIMER:
            OnTimer(hwnd);
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
void OnCreate(HWND hwnd)
{

    SetTimer(hwnd,1,50,NULL);
}
void OnTimer(HWND hwnd)
{
        static face fleft=f2,fright=f1;   //two visible faces thus determine color
        static float left=0,right=LEN,centre=LEN; //x coordinate of the three lines
        static float theta=0;


        theta+=1;
        if(theta==90)
            {
                fright=fleft;
                fleft=(face)((fright+1)%4);
            }
        theta=theta-theta*(int)(theta/90);




        HDC hdc;

        HBRUSH hbr;
        HGDIOBJ holdbr;

        //calculate centre, right, and left

        left=right=LEN*cos((45-theta)/180*3.14)/1.414;
        centre=LEN*sin((45-theta)/180*3.14)/1.414;

        hdc=GetDC(hwnd);

        hbr=CreateSolidBrush ( RGB (255,255,255 ) ) ;
        holdbr = SelectObject ( hdc, hbr ) ;

        Rectangle(hdc,0,0,SIDE+2*CEN,LEN+TOP+100);

        SelectObject ( hdc, holdbr ) ;
        DeleteObject ( hbr ) ;


        hbr=CreateSolidBrush ( RGB (100*fleft, 50*fleft+50, 100*fleft+100 ) ) ;
        holdbr = SelectObject ( hdc, hbr ) ;

        Rectangle(hdc,CEN-left,TOP,CEN-centre,LEN+TOP);

        SelectObject ( hdc, holdbr ) ;
        DeleteObject ( hbr ) ;


        hbr=CreateSolidBrush ( RGB (100*fright, 50*fright+50, 100*fright+100 ) ) ;
        holdbr = SelectObject ( hdc, hbr ) ;

        Rectangle(hdc,CEN-centre,TOP,CEN+right,LEN+TOP);

        SelectObject ( hdc, holdbr ) ;
        DeleteObject ( hbr ) ;

        ReleaseDC(hwnd,hdc);
}
