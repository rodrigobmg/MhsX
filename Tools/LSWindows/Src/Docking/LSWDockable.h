#pragma once

// https://www.codeproject.com/Articles/10224/Docking-Toolbars-in-Plain-C

#include "../LSWWin.h"
#include "../Layout/LSWWidgetLayout.h"
#include "../Widget/LSWWidget.h"

#ifndef LSW_POPUP_STYLES
#define LSW_POPUP_STYLES			(WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_SYSMENU | WS_CAPTION | WS_THICKFRAME)
#endif	// LSW_POPUP_STYLES
#ifndef LSW_POPUP_STYLESEX
#define LSW_POPUP_STYLESEX			(WS_EX_TOOLWINDOW | WS_EX_WINDOWEDGE)
#endif	// LSW_POPUP_STYLESEX
#ifndef LSW_CHILD_STYLES
#define LSW_CHILD_STYLES			(WS_CHILD)
#endif	// LSW_CHILD_STYLES
#ifndef LSW_CHILD_STYLESEX
#define LSW_CHILD_STYLESEX			(WS_EX_TRANSPARENT)
#endif	// LSW_CHILD_STYLESEX

namespace lsw {

	class CDockable : public CWidget {
	public :
		CDockable( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget = true, HMENU _hMenu = NULL );
		~CDockable();


		// == Enumerations.
		// Dock state.
		enum LSW_DOCK_STATE : DWORD {
			LSW_DS_FLOATING					= 0x80,
			LSW_DS_DOCKED_LEFT				= 0x01,
			LSW_DS_DOCKED_RIGHT				= 0x02,
			LSW_DS_DOCKED_TOP				= 0x04,
			LSW_DS_DOCKED_BOTTOM			= 0x08,
			LSW_DS_ALL_DOCKS				= LSW_DS_DOCKED_LEFT | LSW_DS_DOCKED_RIGHT | LSW_DS_DOCKED_TOP | LSW_DS_DOCKED_BOTTOM,

		};

		// Dock styles.
		enum LSW_DOCK_STYLES : DWORD {
			LSW_DS_ALLOW_DOCKLEFT			= 0x01,
			LSW_DS_ALLOW_DOCKRIGHT			= 0x02,
			LSW_DS_ALLOW_DOCKTOP			= 0x04,
			LSW_DS_ALLOW_DOCKBOTTOM			= 0x08,
			LSW_DS_DRAWGRIPPERDOCKED		= 0x00000010,	// Draw a gripper when docked.
			LSW_DS_DRAWGRIPPERFLOATING		= 0x00000020,	// Draw a gripper when floating.
			LSW_DS_KEEPORIGSTATE			= 0x00000040,	// Force the Docking Frame to always stay docked or floating as it was originally created.
			LSW_DS_NORESIZE					= 0x00000080,	// Prevent user from resizing the Docking Frame.
			LSW_DS_DONTSAVEPOS				= 0x00000100,	// Don't save changed position/size. This is primarily set only by the docking library.
			LSW_DS_NODESTROY				= 0x00000200,	// Hides the Docking Frame window instead of destroying it.
			LSW_DS_NODISABLE				= 0x00000400,	// Does not disable the Docking Frame window when DockingEnable() is called, and the window is floating.
			LSW_DS_FREEFLOAT				= 0x00000800,	// Docking Frame window can float behind the container.

			LSW_DS_HIDDEN					= 0x80000000,	// Used only by docking library.
			LSW_DS_ALLOW_DOCKALL			= (LSW_DS_ALLOW_DOCKLEFT | LSW_DS_ALLOW_DOCKBOTTOM | LSW_DS_ALLOW_DOCKRIGHT | LSW_DS_ALLOW_DOCKTOP),
		};



		// == Functions.
		// Gets the last floating rectangle.
		const LSW_RECT &					LastFloatRect() const { return m_rFloatRect; }

		// Gets the last docked rectangle.
		const LSW_RECT &					LastDockedRect() const { return m_rDockedRect; }

		// Gets the 

		// Are we floating?
		bool								Floating() const { return Floating( m_dwState ); }

		// The dockable message handler.
		static LRESULT CALLBACK				WindowProc( HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam );

		// Determines of a state is floating.
		static bool							Floating( DWORD _dwState ) { return (_dwState & LSW_DS_FLOATING) ? true : false; }


	protected :
		// == Enumerations.
		enum LSW_DOCK_DRAG_RECT_TYPE {
			LSW_DDRT_CHECKERED				= 0,
			LSW_DDRT_SOLID					= 1,
		};


		// == Members.
		// Docked rectangle.
		LSW_RECT							m_rDockedRect;

		// Floating rectangle.
		LSW_RECT							m_rFloatRect;

		// State.
		DWORD								m_dwState;

		// Style.
		DWORD								m_dwDockStyle;

		// Frame X.
		INT									m_iFrameX;

		// Frame Y.
		INT									m_iFrameY;

		// Frame width.
		INT									m_iFrameWidth;

		// Frame height.
		INT									m_iFrameHeight;

		// Docked size.
		DWORD								m_dwDockSize;

		// To keep track of window movement.  Only one window can move via the mouse at a time.
		// The dragging rectangle.
		static LSW_RECT						m_rDragPlacementRect;

		// The widget being dragged.
		static CWidget *					m_pwDraggingDockWnd;

		// The hook procedure.
		static HHOOK						m_hOrigDockHookProc;

		// The mouse position.
		static POINT						m_pMousePos;

		// Has the mouse moved?
		static BOOL							m_bMouseMoved;

		// Drag rectangle type.
		static LSW_DOCK_DRAG_RECT_TYPE		m_ddrtDragRectType;


		// == Functions.
		// WM_SIZE.
		virtual LSW_HANDLED					Size( WPARAM _wParam, LONG _lWidth, LONG _lHeight );

		// WM_CANCELMODE.
		virtual LSW_HANDLED					CancelMode();

		// WM_LBUTTONUP.
		virtual LSW_HANDLED					LButtonUp( DWORD _dwVirtKeys, const POINTS &_pCursorPos );

		// WM_MOUSEMOVE.
		virtual LSW_HANDLED					MouseMove( DWORD _dwVirtKeys, const POINTS &_pCursorPos );

		// WM_NCLBUTTONDOWN.
		virtual LSW_HANDLED					NcLButtonDown( INT _iHitTest, const POINTS &_pCursorPos );

		// WM_WINDOWPOSCHANGED.
		virtual LSW_HANDLED					WindowPosChanged( const WINDOWPOS * _pwpPos );

		// Setting the HWND after the control has been created.
		virtual void						InitControl( HWND _hWnd );

		// Become a floating window.
		void								BecomeFloat();

		// Become a normal child window.
		void								BecomeChild();

		// Toggle between floating and being a child.
		void								ToggleFloatAndChild();

		// Check if the rectangle have moved to adocking or non-docking area.
		LSW_DOCK_STATE						CheckDockingPos() const;

		// Determine the size of the floating frame.
		void								CalcFloatFrame();

		// Updates the layout.
		void								UpdateLayout( CWidget * _pwParent );

		// Cancels the drag.
		void								CancelDrag( BOOL _bBecauseOfCancelMode );

		// Redraws the docking state.
		virtual void						RedrawDockingState();

		// Sets the floating window position.
		virtual void						SetFloatingPos( DWORD _dwSetWindowPosFlags );

		// Keyboard hook.
		static LRESULT CALLBACK				KeyboardProc( int _iCode, WPARAM _wParam, LPARAM _lParam );

		// Draw the drag rectangle.
		static void							DrawDragRect();


	private :
	};

}	// namespace lsw