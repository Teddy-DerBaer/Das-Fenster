// Das Fenster.cpp : Definiert den Einstiegspunkt für die Anwendung.
//

#include "stdafx.h"
#include "Das Fenster.h"

#define MAX_LOADSTRING 100

// Globale Variablen:
HINSTANCE hInst;                                // Aktuelle Instanz
WCHAR szTitle[MAX_LOADSTRING];                  // Titelleistentext
WCHAR szWindowClass[MAX_LOADSTRING];            // Klassenname des Hauptfensters


// Vorwärtsdeklarationen der in diesem Codemodul enthaltenen Funktionen:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,					//Das Mutter Fenster (Fenster.exe) wird eine Instance handle (Fenster Nummer ) von Windows zugewiesen darüber ist es erreichbar
                     _In_opt_ HINSTANCE hPrevInstance,			//hPrevInstance hat keine Bedeutung. Es wurde in 16-Bit-Windows verwendet, es ist aber jetzt stets 0 (null).
                     _In_ LPWSTR    lpCmdLine,					//pCmdLine enthält die Befehlszeilenargumente als Unicode - Zeichenfolge
                     _In_ int       nCmdShow)					//nCmdShow ist ein Flag, das angibt, ob das Hauptanwendungsfenster minimiert, maximiert oder in Normalgröße angezeigt wird
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Hier Code einfügen.

    
	// Globale Zeichenfolgen initialisieren
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DASFENSTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Anwendungsinitialisierung ausführen:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }



	//Ein Tastaturbeschleuniger (oder einfach Beschleuniger) ist ein Tastenanschlag
	//oder eine Tastenkombination, die eine
	//WM_COMMAND- oder WM_SYSCOMMAND- Nachricht für eine Anwendung generiert .
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DASFENSTER));

	//Enthält die Nachrichten für das Fenster was es machen soll
    MSG msg;

    // Hauptnachrichtenschleife:
	//Diese läuft solange wie das Fenster existiert
    while (GetMessage(&msg, nullptr, 0, 0))
    {


		//Verarbeitet Zugriffstasten für Menübefehle.Die Funktion übersetzt eine
		//WM_KEYDOWN - oder eine WM_SYSKEYDOWN - Nachricht in eine WM_COMMAND
		//oder eine WM_SYSCOMMAND - Nachricht(wenn in der angegebenen Beschleunigungstabelle ein Eintrag für den Schlüssel vorhanden ist)
		//und sendet dann die WM_COMMAND - oder WM_SYSCOMMAND - Nachricht direkt an die angegebene Fensterprozedur.
		//TranslateAccelerator gibt erst zurück, wenn die Fensterprozedur die Nachricht verarbeitet hat.
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
			//Übersetzt virtuelle Schlüsselnachrichten in Zeichennachrichten.
			//Die Zeichenmeldungen werden an die Nachrichtenwarteschlange des aufrufenden Threads gesendet
			//damit sie beim nächsten Aufruf der GetMessage - oder PeekMessage - Funktion vom Thread gelesen werden.
            TranslateMessage(&msg);

			//Versendet eine Nachricht an eine Fensterprozedur.Es wird normalerweise verwendet
			//um eine Nachricht zu senden, die von der GetMessage - Funktion abgerufen wird
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNKTION: MyRegisterClass()
//
//  ZWECK: Registriert die Fensterklasse.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DASFENSTER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DASFENSTER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNKTION: InitInstance(HINSTANCE, int)
//
//   ZWECK: Speichert das Instanzenhandle und erstellt das Hauptfenster.
//
//   KOMMENTARE:
//
//        In dieser Funktion wird das Instanzenhandle in einer globalen Variablen gespeichert, und das
//        Hauptprogrammfenster wird erstellt und angezeigt.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Instanzenhandle in der globalen Variablen speichern

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNKTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ZWECK:  Verarbeitet Meldungen vom Hauptfenster.
//
//  WM_COMMAND  - Verarbeiten des Anwendungsmenüs
//  WM_PAINT    - Darstellen des Hauptfensters
//  WM_DESTROY  - Ausgeben einer Beendenmeldung und zurückkehren
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Menüauswahl bearbeiten:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            //TODO: Zeichencode, der hdc verwendet, hier einfügen...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Meldungshandler für Infofeld.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
