#pragma once

#include "../LSWWin.h"
#include "../Expressions/LSWExpression.h"
#include "../Helpers/LSWHelpers.h"
#include "../Layout/LSWWidgetLayout.h"

#include <vector>

namespace lsw {

	class CWidget {
		friend class						CDockable;
		friend class						CLayoutManager;
	public :
		CWidget( const LSW_WIDGET_LAYOUT &_wlLayout, CWidget * _pwParent, bool _bCreateWidget = true, HMENU _hMenu = NULL );
		virtual ~CWidget();


		// == Enumerations.
		enum LSW_HANDLED {
			LSW_H_HANDLED,					// The message was handled and the default procedure should not be called.
			LSW_H_CONTINUE,					// Continue and let the default procedure handle it.
		};


		// == Functions.
		// The default message handler.
		static LRESULT CALLBACK				WindowProc( HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam );

		// The default dialog message handler.
		static INT_PTR CALLBACK				DialogProc( HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam );


		// The Window handle.
		HWND								Wnd() const { return m_hWnd; }

		// The parent widget.
		CWidget *							Parent() { return m_pwParent; }

		// The parent widget.
		const CWidget *						Parent() const { return m_pwParent; }

		// The ancestor widget.
		CWidget *							Ancestor();

		// The ancestor widget.
		const CWidget *						Ancestor() const;

		// Custom ID.
		WORD								Id() const { return m_wId; }

		// Enabled or disabled.
		BOOL								Enabled() const { return m_bEnabled; }

		// Enable or disable.
		BOOL								SetEnabled( BOOL _bEnable ) { m_bEnabled = (_bEnable != 0); return ::EnableWindow( Wnd(), m_bEnabled ); }

		// Is visible.
		BOOL								Visible() const { return ::IsWindowVisible( Wnd() ); }

		// Set visible or not.
		BOOL								SetVisible( BOOL _bVis ) { return ::ShowWindow( Wnd(), _bVis ? SW_SHOW : SW_HIDE ); }

		// Get the window style.
		DWORD								GetStyle() const { return static_cast<DWORD>(::GetWindowLongW( Wnd(), GWL_STYLE )); }

		// Get the window extended style.
		DWORD								GetStyleEx() const { return static_cast<DWORD>(::GetWindowLongW( Wnd(), GWL_EXSTYLE )); }

		// Set the window style.  Returns the previous style.
		DWORD								SetStyle( DWORD _dwStyle ) { return static_cast<DWORD>(::SetWindowLongW( Wnd(), GWL_STYLE, static_cast<LONG>(_dwStyle) )); }

		// Set the window extended style.  Returns the previous extended style.
		DWORD								SetStyleEx( DWORD _dwStyle ) { return static_cast<DWORD>(::SetWindowLongW( Wnd(), GWL_EXSTYLE, static_cast<LONG>(_dwStyle) )); }

		// Adds a flag to the current style of the window.
		DWORD								AddStyle( DWORD _dwFlags ) { return SetStyle( GetStyle() | _dwFlags ); }

		// Adds a flag to the current extended style of the window.
		DWORD								AddStyleEx( DWORD _dwFlags ) { return SetStyleEx( GetStyleEx() | _dwFlags ); }

		// Removes a flag from the current style of the window.
		DWORD								RemoveStyle( DWORD _dwFlags ) { return SetStyle( GetStyle() & ~_dwFlags ); }

		// Removes a flag from the current extended style of the window.
		DWORD								RemoveStyleEx( DWORD _dwFlags ) { return SetStyleEx( GetStyleEx() & ~_dwFlags ); }

		// Copies the text of the specified window's title bar (if it has one) into a buffer. If the specified window is a control, the text of the control is copied.
		virtual INT							GetTextA( LPSTR _lpString, INT _nMaxCount ) const { return ::GetWindowTextA( Wnd(), _lpString, _nMaxCount ); }

		// Copies the text of the specified window's title bar (if it has one) into a buffer. If the specified window is a control, the text of the control is copied.
		virtual INT							GetTextW( LPWSTR _lpString, INT _nMaxCount ) const { return ::GetWindowTextW( Wnd(), _lpString, _nMaxCount ); }

		// Gets the window text.
		virtual std::string					GetTextA() const;

		// Gets the window text.
		virtual std::wstring				GetTextW() const;

		// Retrieves the length, in characters, of the specified window's title bar text (if the window has a title bar).
		//	If the specified window is a control, the function retrieves the length of the text within the control
		virtual INT							GetTextLengthA() const { return ::GetWindowTextLengthA( Wnd() ); }

		// Retrieves the length, in characters, of the specified window's title bar text (if the window has a title bar).
		//	If the specified window is a control, the function retrieves the length of the text within the control
		virtual INT							GetTextLengthW() const { return ::GetWindowTextLengthW( Wnd() ); }

		// Changes the text of the specified window's title bar (if it has one). If the specified window is a control, the text of the control is changed.
		// String is assumed to be UTF-8 and is converted to UTF-16 internally.
		virtual BOOL						SetTextA( LPCSTR _lpString );

		// Changes the text of the specified window's title bar (if it has one). If the specified window is a control, the text of the control is changed.
		virtual BOOL						SetTextW( LPCWSTR _lpwString ) { return ::SetWindowTextW( Wnd(), _lpwString ); }

		// Get the value of the text as an expression.
		BOOL								GetTextAsExpression( ee::CExpEvalContainer::EE_RESULT &_eResult, BOOL * _pbExpIsValid = nullptr ) const;

		// Get the value of the text as an int64_t expression.
		BOOL								GetTextAsInt64Expression( ee::CExpEvalContainer::EE_RESULT &_eResult ) const;

		// Get the value of the text as a uint64_t expression.
		BOOL								GetTextAsUInt64Expression( ee::CExpEvalContainer::EE_RESULT &_eResult ) const;

		// Get the value of the text as a double expression.
		BOOL								GetTextAsDoubleExpression( ee::CExpEvalContainer::EE_RESULT &_eResult ) const;

		// If the function succeeds, the return value is the pointer to the window that previously had the keyboard focus.
		CWidget *							SetFocus() const;

		// Selects a range of text.  Implemented by CEdit.
		virtual VOID						SetSel( INT _iStart, INT _iEnd ) const {}

		// Are we checked?  Implemented by CCheckButton and CRadioButton.
		virtual BOOL						IsChecked() const { return FALSE; }

		// Changes the check state of a button control.  Implemented by CCheckButton and CRadioButton.
		virtual VOID						CheckButton( UINT _uCheck ) {}

		// Sets the button state to BST_CHECKED.
		virtual VOID						Check() { CheckButton( BST_CHECKED ); }

		// Sets the button state to BST_UNCHECKED.
		virtual VOID						UnCheck() { CheckButton( BST_UNCHECKED ); }

		// Sets the button to BST_CHECKED or BST_UNCHECKED.
		virtual VOID						SetCheck( BOOL _bChecked ) { CheckButton( _bChecked ? BST_CHECKED : BST_UNCHECKED ); }

		// Sets the parent window.
		virtual CWidget *					SetParent( CWidget * _pwParent );

		// Window rectangle.
		//virtual const LSW_RECT &			WindowRect() const { return m_rRect; }
		virtual const LSW_RECT				WindowRect( const CWidget * pwChild ) const { LSW_RECT rTemp; ::GetWindowRect( Wnd(), &rTemp ); return rTemp; }

		// Client rectangle.
		//virtual const LSW_RECT &			ClientRect() const { return m_rClientRect; }
		virtual const LSW_RECT				ClientRect( const CWidget * pwChild ) const { LSW_RECT rTemp; ::GetClientRect( Wnd(), &rTemp ); return rTemp; }

		// Starting window rectangle.
		virtual const LSW_RECT &			StartRect() const { return m_rStartingRect; }

		// This control's starting window rectangle relative to its parent's starting client rectangle.
		virtual const LSW_RECT &			StartClientRect() const { return m_rStartingClientRect; }

		// Virtual client rectangle.  Can be used for things that need to be adjusted based on whether or not status bars, toolbars, etc. are present.
		// pwChild can be nullptr.  If not nullptr, it is assumed to be a child of the widget, and this widget might create a specific rectangle for
		//	the pwChild, such as for splitter controls.
		virtual const LSW_RECT				VirtualClientRect( const CWidget * pwChild ) const { return ClientRect( pwChild ); }

		// Updates all rectangles with the current window rectangles.  If a control changes size and you wish to set the new size as its "base" size,
		//	call this.
		VOID								UpdateRects();

		// Do we have a given child widget?
		bool								HasChild( const CWidget * _pwChild ) const;

		// Gets a pointer to a child with the given ID.
		CWidget *							FindChild( WORD _wId );

		// Gets a pointer to a child with the given ID.
		const CWidget *						FindChild( WORD _wId ) const;

		// Sets a given font on all children of a window.
		static BOOL CALLBACK				EnumChildWindows_SetFont( HWND _hWnd, LPARAM _lParam );

		// Converts a point from pixels to dialog units.
		static POINT						PixelsToDialogUnits( HWND _hWnd, LONG _lX, LONG _lY );


	protected :
		// == Members.
		// The window handle.
		HWND								m_hWnd;

		// Custom ID.
		WORD								m_wId;

		// Enabled.
		BOOL								m_bEnabled;

		// The window rectangle.
		//LSW_RECT							m_rRect;

		// The client rectangle.
		//LSW_RECT							m_rClientRect;

		// Original rectangle.
		LSW_RECT							m_rStartingRect;

		// This object's starting window rect in relationship with the parent's starting client rect.
		LSW_RECT							m_rStartingClientRect;

		// Extended styles.
		DWORD								m_dwExtendedStyles;

		// Default state.  Depends on the type of control.
		BOOL								m_bActive;

		// Children.
		std::vector<CWidget *>				m_vChildren;

		// Parent.
		CWidget *							m_pwParent;

		// Width expression.
		CExpression							m_eWidth;

		// Height expression.
		CExpression							m_eHeight;

		// Left expression.
		CExpression							m_eLeft;

		// Right expression.
		CExpression							m_eRight;

		// Top expression.
		CExpression							m_eTop;

		// Bottom expression.
		CExpression							m_eBottom;

		// Dock windows as children of this window.
		std::vector<CDockable *>			m_vDockables;

		// Show as active or not.
		BOOL								m_bShowAsActive;

		// Last hit returned by NcHitTest().
		INT									m_iLastHit;


		// == Message Handlers.
		// WM_NCCREATE.
		virtual LSW_HANDLED					NcCreate( const CREATESTRUCTW &_csCreateParms ) { return LSW_H_CONTINUE; }

		// WM_CREATE.
		virtual LSW_HANDLED					Create( const CREATESTRUCTW &_csCreateParms ) { return LSW_H_CONTINUE; }

		// WM_INITDIALOG.
		virtual LSW_HANDLED					InitDialog() { return LSW_H_CONTINUE; };

		// WM_DESTROY.
		virtual LSW_HANDLED					Destroy() { return LSW_H_CONTINUE; }

		// WM_NCDESTROY.
		virtual LSW_HANDLED					NcDestroy() { return LSW_H_CONTINUE; }

		// WM_CLOSE.
		virtual LSW_HANDLED					Close() { return LSW_H_CONTINUE; }

		// WM_CANCELMODE.
		virtual LSW_HANDLED					CancelMode() { return LSW_H_CONTINUE; }

		// WM_SIZE.
		virtual LSW_HANDLED					Size( WPARAM _wParam, LONG _lWidth, LONG _lHeight );

		// WM_SIZE, SIZE_MINIMIZED.
		virtual LSW_HANDLED					Minimized( LONG _lWidth, LONG _lHeight ) { return LSW_H_CONTINUE; }

		// WM_MOVE.
		virtual LSW_HANDLED					Move( LONG _lX, LONG _lY );

		// WM_WINDOWPOSCHANGED.
		virtual LSW_HANDLED					WindowPosChanged( const WINDOWPOS * _pwpPos ) { return LSW_H_CONTINUE; }

		// WM_COMMAND from control.
		virtual LSW_HANDLED					Command( WORD _wCtrlCode, WORD _Id, CWidget * _pwSrc ) { return LSW_H_CONTINUE; }

		// WM_COMMAND from menu.
		virtual LSW_HANDLED					MenuCommand( WORD _Id ) { return LSW_H_CONTINUE; }

		// WM_COMMAND from accelerator.
		virtual LSW_HANDLED					AcceleratorCommand( WORD _Id ) { return LSW_H_CONTINUE; }

		// WM_NOTIFY->NM_DBLCLK on this item (if LSW_HANDLED::LSW_H_CONTINUE, message is passed to owning window).
		virtual LSW_HANDLED					DblClk( const NMHDR * _phHdr ) { return LSW_H_CONTINUE; }

		// WM_NOTIFY->NM_DBLCLK for the owning window if the child either could not be resolved or returned LSW_HANDLED::LSW_H_CONTINUE.
		virtual LSW_HANDLED					DblClk( const NMHDR * _phHdr, WORD _wControlId, CWidget * _pwWidget ) { return LSW_H_CONTINUE; }

		// WM_ERASEBKGND.
		virtual LSW_HANDLED					EraseBkgnd( HDC _hDc ) { return LSW_H_CONTINUE; }

		// WM_PAINT.
		virtual LSW_HANDLED					Paint() { return LSW_H_CONTINUE; }

		// WM_NCPAINT.
		virtual LSW_HANDLED					NcPaint( HRGN _hRgn ) { return LSW_H_CONTINUE; }

		// WM_CTLCOLORSTATIC.
		virtual LSW_HANDLED					CtlColorStatic( HDC _hDc, CWidget * _pwControl, HBRUSH &_hBrush ) { return LSW_H_CONTINUE; }

		// WM_SETCURSOR.
		virtual LSW_HANDLED					SetCursor( CWidget * _pwControl, WORD _wHitTest, WORD _wIdent ) { return LSW_H_CONTINUE; }

		// WM_ACTIVATE.
		virtual LSW_HANDLED					Activate( BOOL _bMinimized, WORD _wActivationMode, CWidget * _pwWidget ) { return LSW_H_CONTINUE; }

		// WM_NCACTIVATE.
		virtual LSW_HANDLED					NcActivate( BOOL _bTitleBarActive, LPARAM _lParam ) { m_bShowAsActive = _bTitleBarActive; return LSW_H_CONTINUE; }

		// WM_ENABLE.
		virtual LSW_HANDLED					Enable( BOOL _bEnabled ) { return LSW_H_CONTINUE; }

		// WM_CAPTURECHANGED.
		virtual LSW_HANDLED					CaptureChanged( CWidget * _pwNewCaptureOwner ) { return LSW_H_CONTINUE; }

		// WM_LBUTTONDBLCLK.
		virtual LSW_HANDLED					LButtonDblClk( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_LBUTTONDOWN.
		virtual LSW_HANDLED					LButtonDown( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_LBUTTONUP.
		virtual LSW_HANDLED					LButtonUp( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_MBUTTONDBLCLK.
		virtual LSW_HANDLED					MButtonDblClk( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_MBUTTONDOWN.
		virtual LSW_HANDLED					MButtonDown( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_MBUTTONUP.
		virtual LSW_HANDLED					MButtonUp( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_MOUSEACTIVATE.
		virtual LSW_HANDLED					MouseActivate( CWidget * _pwTopLevelParent, INT _iHitTest, INT &_iReturnCode ) { return LSW_H_CONTINUE; }

		// WM_MOUSEHOVER.
		virtual LSW_HANDLED					MouseHover( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_MOUSEHWHEEL.
		virtual LSW_HANDLED					MouseHWheel( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_MOUSELEAVE.
		virtual LSW_HANDLED					MouseLeave()  { return LSW_H_CONTINUE; }
		
		// WM_MOUSEMOVE.
		virtual LSW_HANDLED					MouseMove( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_MOUSEWHEEL.
		virtual LSW_HANDLED					MouseWheel( DWORD _dwVirtKeys, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCHITTEST.
		virtual LSW_HANDLED					NcHitTest( const POINTS &_pCursorPos, INT &_iReturnHitTest ) { return LSW_H_CONTINUE; }

		// WM_NCLBUTTONDBLCLK.
		virtual LSW_HANDLED					NcButtonDblClk( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCLBUTTONDOWN.
		virtual LSW_HANDLED					NcLButtonDown( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCLBUTTONUP.
		virtual LSW_HANDLED					NcLButtonUp( INT _iHitTest, const POINTS &_pCursorPos ) {
			return LSW_H_CONTINUE;
		}

		// WM_NCMBUTTONDBLCLK.
		virtual LSW_HANDLED					NcMButtonDblClk( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCMBUTTONDOWN.
		virtual LSW_HANDLED					NcMButtonDown( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCMBUTTONUP.
		virtual LSW_HANDLED					NcMButtonUp( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCMOUSEHOVER.
		virtual LSW_HANDLED					NcMouseHover( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCMOUSELEAVE.
		virtual LSW_HANDLED					NcMouseLeave() { return LSW_H_CONTINUE; }

		// WM_NCMOUSEMOVE.
		virtual LSW_HANDLED					NcMouseMove( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCRBUTTONDBLCLK.
		virtual LSW_HANDLED					NcRButtonDblClk( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCRBUTTONDOWN.
		virtual LSW_HANDLED					NcRButtonDown( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCRBUTTONUP.
		virtual LSW_HANDLED					NcRButtonUp( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCXBUTTONDBLCLK.
		virtual LSW_HANDLED					NcXButtonDblClk( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCXBUTTONDOWN.
		virtual LSW_HANDLED					NcXButtonDown( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_NCXBUTTONUP.
		virtual LSW_HANDLED					NcXButtonUp( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_RBUTTONDBLCLK.
		virtual LSW_HANDLED					RButtonDblClk( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_RBUTTONDOWN.
		virtual LSW_HANDLED					RButtonDown( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_RBUTTONUP.
		virtual LSW_HANDLED					RButtonUp( INT _iHitTest, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_XBUTTONDBLCLK.
		virtual LSW_HANDLED					XButtonDblClk( DWORD _dwVirtKeys, DWORD _dwButton, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_XBUTTONDOWN.
		virtual LSW_HANDLED					XButtonDown( DWORD _dwVirtKeys, DWORD _dwButton, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// WM_XBUTTONUP.
		virtual LSW_HANDLED					XButtonUp( DWORD _dwVirtKeys, DWORD _dwButton, const POINTS &_pCursorPos ) { return LSW_H_CONTINUE; }

		// TBN_QUERYINSERT.
		virtual LSW_HANDLED					TbnQueryInsert( const LPNMTOOLBARW _lptbToolBar ) { return LSW_H_CONTINUE; }

		// TBN_QUERYDELETE.
		virtual LSW_HANDLED					TbnQueryDelete( const LPNMTOOLBARW _lptbToolBar ) { return LSW_H_CONTINUE; }

		// TBN_RESET.
		virtual LSW_HANDLED					TbnReset() { return LSW_H_CONTINUE; }

		// TBN_GETBUTTONINFO.
		virtual LSW_HANDLED					TbnGetButtonInfo( LPNMTOOLBARW _lptbToolBar ) { return LSW_H_CONTINUE; }


		// == Functions.
		// Remove a child.
		virtual void						RemoveChild( const CWidget * _pwChild );

		// Add a child.
		void								AddChild( CWidget * _pwChild );

		// Informs that a child was removed from a child control (IE this control's child had a child control removed from it).
		// Is also called on the control from which a child was removed for convenience.
		virtual void						ChildWasRemoved( const CWidget * _pwChild );

		// Set the parent.
		void								SetWidgetParent( CWidget * _pwParent );

		// Evaluates expressions to determine a new rectangle for the control.
		virtual void						EvalNewSize();

		// Setting the HWND after the control has been created.
		virtual void						InitControl( HWND _hWnd );

		// Adds a dockable window to the list of dockable windows.
		void								AddDockable( CDockable * _pdDock );

		// Removes a dockable window from the list of dockable windows.
		void								RemDockable( CDockable * _pdDock );

		// Gets the array of dockables, optionally including this object.
		void								GetDockables( std::vector<CWidget *> &_vReturn, BOOL _bIncludeParent );

		// Handle WM_NCACTIVATE for dockables.  Should be called on the owner window.
		//	_pwWnd = Pointer to window that received WM_NCACTIVATE (can be the owner or one of its tool windows).
		//	_wParam = WPARAM of the WM_NCACTIVATE message.
		//	_lParam = LPARAM of the WM_NCACTIVATE message.
		LRESULT CALLBACK					DockNcActivate( CWidget * _pwWnd, WPARAM _wParam, LPARAM _lParam, BOOL _bCallDefault );

		// Handle WM_ENABLE for Should be called on the owner window.
		//	_pwWnd = Pointer to window that received WM_ENABLE (can be the owner or one of its tool windows).
		//	_wParam = WPARAM of the WM_ENABLE message.
		//	_lParam = LPARAM of the WM_ENABLE message.
		LRESULT CALLBACK					DockEnable( CWidget * _pwWnd, WPARAM _wParam, LPARAM _lParam, BOOL _bCallDefault );

		// Attaches a control/window to its CWidget.
		static BOOL CALLBACK				EnumChildWindows_AttachWindowToWidget( HWND _hWnd, LPARAM _lParam );

		// Applies enabled/disabled settings.
		static BOOL CALLBACK				EnumChildWindows_SetEnabled( HWND _hWnd, LPARAM _lParam );

		// Sets all the starting rectangles for all widgets.
		static BOOL CALLBACK				EnumChildWindows_SetStartingRect( HWND _hWnd, LPARAM _lParam );

		// Resizes all controls when the window resizes.
		static BOOL CALLBACK				EnumChildWindows_ResizeControls( HWND _hWnd, LPARAM _lParam );

		// Evaluates "??" inside expressions.  ?? = this pointer.
		static bool __stdcall				WidgetUserVarHandler( uintptr_t _uiptrData, ee::CExpEvalContainer * _peecContainer, ee::CExpEvalContainer::EE_RESULT &_rResult );

		// Evaluates member access in expressions.
		static bool __stdcall				WidgetMemberAccessHandler( const ee::CExpEvalContainer::EE_RESULT &_rLeft, const std::string &_sMember, uintptr_t _uiptrData, ee::CExpEvalContainer * _peecContainer, ee::CExpEvalContainer::EE_RESULT &_rResult );

		// Handles control setup.
		static VOID							ControlSetup( CWidget * _pwParent, const std::vector<CWidget *> &_vWidgetList );

		// The default message handler.
		static VOID CALLBACK				WndDlgProc( HWND _hWnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam, BOOL _bIsDlg, LRESULT &_lrWndResult, INT_PTR &_ipDiagResult );

	};

}	// namespace lsw
