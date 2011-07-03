#ifndef _PH_TREENEWP_H
#define _PH_TREENEWP_H

typedef struct _PH_TREENEW_CONTEXT
{
    HWND Handle;
    PVOID InstanceHandle;
    HWND FixedHeaderHandle;
    HWND HeaderHandle;
    HWND VScrollHandle;
    HWND HScrollHandle;
    HWND FillerBoxHandle;
    HWND TooltipsHandle;

    union
    {
        struct
        {
            ULONG FontOwned : 1;
            ULONG Tracking : 1; // tracking for fixed divider
            ULONG VScrollVisible : 1;
            ULONG HScrollVisible : 1;
            ULONG FixedColumnVisible : 1;
            ULONG CanAnyExpand : 1;
            ULONG TriState : 1;
            ULONG HasFocus : 1;
            ULONG ThemeInitialized : 1; // delay load theme data
            ULONG ThemeActive : 1;
            ULONG ThemeHasItemBackground : 1;
            ULONG ThemeHasGlyph : 1;
            ULONG ThemeHasHotGlyph : 1;
            ULONG FocusNodeFound : 1; // used to preserve the focused node across restructuring
            ULONG SearchFailed : 1; // used to prevent multiple beeps
            ULONG SearchSingleCharMode : 1; // LV style single-character search
            ULONG TooltipUnfolding : 1; // whether the current tooltip is unfolding
            ULONG DoubleBuffered : 1;
            ULONG SuspendUpdateLayout : 1;
            ULONG Spare : 13;
        };
        ULONG Flags;
    };
    ULONG Style;
    ULONG ExtendedStyle;

    HFONT Font;
    HCURSOR Cursor;

    RECT ClientRect;
    LONG HeaderHeight;
    LONG RowHeight;
    ULONG VScrollWidth;
    ULONG HScrollHeight;
    LONG VScrollPosition;
    LONG HScrollPosition;
    LONG FixedWidth; // width of the fixed part of the tree list
    LONG FixedWidthMinimum;
    LONG NormalLeft; // FixedWidth + 1 if there is a fixed column, otherwise 0
    LONG TrackStartX;
    LONG TrackOldFixedWidth;

    PPH_TREENEW_NODE HotNode;
    PPH_TREENEW_NODE FocusNode;
    PPH_TREENEW_NODE MarkNode; // selection mark

    ULONG MouseDownLast;
    POINT MouseDownLocation;

    PPH_TREENEW_CALLBACK Callback;
    PVOID CallbackContext;

    PPH_TREENEW_COLUMN *Columns; // columns, indexed by ID
    ULONG NextId;
    ULONG AllocatedColumns;
    ULONG NumberOfColumns; // just a statistic; do not use for actual logic

    PPH_TREENEW_COLUMN *ColumnsByDisplay; // columns, indexed by display order (excluding the fixed column)
    ULONG AllocatedColumnsByDisplay;
    ULONG NumberOfColumnsByDisplay; // the number of visible columns (excluding the fixed column)
    LONG TotalViewX; // total width of normal columns
    PPH_TREENEW_COLUMN FixedColumn;
    PPH_TREENEW_COLUMN FirstColumn;

    PPH_LIST FlatList;

    ULONG SortColumn; // ID of the column to sort by
    PH_SORT_ORDER SortOrder;

    LONG SearchMessageTime;
    PWSTR SearchString;
    ULONG SearchStringCount;
    ULONG AllocatedSearchString;

    ULONG TooltipIndex;
    ULONG TooltipId;
    PPH_STRING TooltipText;
    RECT TooltipRect; // text rectangle of an unfolding tooltip
    HFONT TooltipFont;
    HFONT NewTooltipFont;

    TEXTMETRIC TextMetrics;
    HTHEME ThemeData;

    HDC BufferedContext;
    HBITMAP BufferedOldBitmap;
    HBITMAP BufferedBitmap;
    RECT BufferedContextRect;

    LONG EnableRedraw;
    HRGN SuspendUpdateRegion;
} PH_TREENEW_CONTEXT, *PPH_TREENEW_CONTEXT;

LRESULT CALLBACK PhTnpWndProc(
    __in HWND hwnd,
    __in UINT uMsg,
    __in WPARAM wParam,
    __in LPARAM lParam
    );

BOOLEAN NTAPI PhTnpNullCallback(
    __in HWND hwnd,
    __in PH_TREENEW_MESSAGE Message,
    __in_opt PVOID Parameter1,
    __in_opt PVOID Parameter2,
    __in_opt PVOID Context
    );

VOID PhTnpCreateTreeNewContext(
    __out PPH_TREENEW_CONTEXT *Context
    );

VOID PhTnpDestroyTreeNewContext(
    __in PPH_TREENEW_CONTEXT Context
    );

// Event handlers

BOOLEAN PhTnpOnCreate(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in CREATESTRUCT *CreateStruct
    );

VOID PhTnpOnSize(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpOnSetFont(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in HFONT Font,
    __in LOGICAL Redraw
    );

VOID PhTnpOnSettingChange(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpOnThemeChanged(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context
    );

BOOLEAN PhTnpOnSetCursor(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in HWND CursorWindowHandle
    );

VOID PhTnpOnPaint(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpOnPrintClient(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in HDC hdc,
    __in ULONG Flags
    );

VOID PhTnpOnMouseMove(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG VirtualKeys,
    __in LONG CursorX,
    __in LONG CursorY
    );

VOID PhTnpOnMouseLeave(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpOnXxxButtonXxx(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Message,
    __in ULONG VirtualKeys,
    __in LONG CursorX,
    __in LONG CursorY
    );

VOID PhTnpOnCaptureChanged(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpOnKeyDown(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG VirtualKey,
    __in ULONG Data
    );

VOID PhTnpOnChar(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Character,
    __in ULONG Data
    );

VOID PhTnpOnMouseWheel(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in LONG Distance,
    __in ULONG VirtualKeys,
    __in LONG CursorX,
    __in LONG CursorY
    );

VOID PhTnpOnContextMenu(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in LONG CursorScreenX,
    __in LONG CursorScreenY
    );

VOID PhTnpOnVScroll(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Request
    );

VOID PhTnpOnHScroll(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Request
    );

BOOLEAN PhTnpOnNotify(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in NMHDR *Header,
    __out LRESULT *Result
    );

ULONG_PTR PhTnpOnUserMessage(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Message,
    __in ULONG_PTR WParam,
    __in ULONG_PTR LParam
    );

// Misc.

VOID PhTnpUpdateTextMetrics(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpUpdateThemeData(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpCancelTrack(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpLayout(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpSetFixedWidth(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG FixedWidth
    );

VOID PhTnpSetRedraw(
    __in PPH_TREENEW_CONTEXT Context,
    __in BOOLEAN Redraw
    );

// Columns

PPH_TREENEW_COLUMN PhTnpLookupColumnById(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Id
    );

BOOLEAN PhTnpAddColumn(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPH_TREENEW_COLUMN Column
    );

BOOLEAN PhTnpRemoveColumn(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Id
    );

BOOLEAN PhTnpCopyColumn(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Id,
    __out PPH_TREENEW_COLUMN Column
    );

BOOLEAN PhTnpChangeColumn(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Mask,
    __in ULONG Id,
    __in PPH_TREENEW_COLUMN Column
    );

VOID PhTnpExpandAllocatedColumns(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpUpdateColumnMaps(
    __in PPH_TREENEW_CONTEXT Context
    );

// Columns (header control)

LONG PhTnpInsertColumnHeader(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPH_TREENEW_COLUMN Column
    );

VOID PhTnpChangeColumnHeader(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Mask,
    __in PPH_TREENEW_COLUMN Column
    );

VOID PhTnpDeleteColumnHeader(
    __in PPH_TREENEW_CONTEXT Context,
    __inout PPH_TREENEW_COLUMN Column
    );

VOID PhTnpUpdateColumnHeaders(
    __in PPH_TREENEW_CONTEXT Context
    );

BOOLEAN PhTnpSetColumnHeaderSortIcon(
    __in PPH_TREENEW_CONTEXT Context,
    __in_opt PPH_TREENEW_COLUMN SortColumnPointer
    );

// Nodes

BOOLEAN PhTnpGetNodeChildren(
    __in PPH_TREENEW_CONTEXT Context,
    __in_opt PPH_TREENEW_NODE Node,
    __out PPH_TREENEW_NODE **Children,
    __out PULONG NumberOfChildren
    );

BOOLEAN PhTnpIsNodeLeaf(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPH_TREENEW_NODE Node
    );

BOOLEAN PhTnpGetCellText(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPH_TREENEW_NODE Node,
    __in ULONG Id,
    __out PPH_STRINGREF Text
    );

VOID PhTnpRestructureNodes(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpInsertNodeChildren(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPH_TREENEW_NODE Node,
    __in ULONG Level
    );

VOID PhTnpSetExpandedNode(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPH_TREENEW_NODE Node,
    __in BOOLEAN Expanded
    );

BOOLEAN PhTnpGetCellParts(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Index,
    __in_opt PPH_TREENEW_COLUMN Column,
    __in ULONG Flags,
    __out PPH_TREENEW_CELL_PARTS Parts
    );

BOOLEAN PhTnpGetRowRects(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Start,
    __in ULONG End,
    __in BOOLEAN Clip,
    __out PRECT Rect
    );

VOID PhTnpHitTest(
    __in PPH_TREENEW_CONTEXT Context,
    __inout PPH_TREENEW_HIT_TEST HitTest
    );

VOID PhTnpSelectRange(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Start,
    __in ULONG End,
    __in ULONG Flags,
    __out_opt PULONG ChangedStart,
    __out_opt PULONG ChangedEnd
    );

VOID PhTnpSetHotNode(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPH_TREENEW_NODE NewHotNode,
    __in BOOLEAN NewPlusMinusHot
    );

BOOLEAN PhTnpEnsureVisibleNode(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Index
    );

// Keyboard

BOOLEAN PhTnpProcessFocusKey(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG VirtualKey
    );

BOOLEAN PhTnpProcessNodeKey(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG VirtualKey
    );

VOID PhTnpProcessSearchKey(
    __in PPH_TREENEW_CONTEXT Context,
    __in ULONG Character
    );

BOOLEAN PhTnpDefaultIncrementalSearch(
    __in PPH_TREENEW_CONTEXT Context,
    __inout PPH_TREENEW_SEARCH_EVENT SearchEvent,
    __in BOOLEAN Partial,
    __in BOOLEAN Wrap
    );

// Scrolling

VOID PhTnpUpdateScrollBars(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpScroll(
    __in PPH_TREENEW_CONTEXT Context,
    __in LONG DeltaRows,
    __in LONG DeltaX
    );

VOID PhTnpProcessVerticalScroll(
    __in PPH_TREENEW_CONTEXT Context,
    __in LONG DeltaRows
    );

VOID PhTnpProcessHorizontalScroll(
    __in PPH_TREENEW_CONTEXT Context,
    __in LONG DeltaX
    );

// Drawing

VOID PhTnpPaint(
    __in HWND hwnd,
    __in PPH_TREENEW_CONTEXT Context,
    __in HDC hdc,
    __in PRECT PaintRect
    );

VOID PhTnpPrepareRowForDraw(
    __in PPH_TREENEW_CONTEXT Context,
    __in HDC hdc,
    __inout PPH_TREENEW_NODE Node
    );

VOID PhTnpDrawCell(
    __in PPH_TREENEW_CONTEXT Context,
    __in HDC hdc,
    __in PRECT CellRect,
    __in PPH_TREENEW_NODE Node,
    __in PPH_TREENEW_COLUMN Column,
    __in LONG RowIndex,
    __in LONG ColumnIndex
    );

VOID PhTnpDrawDivider(
    __in PPH_TREENEW_CONTEXT Context,
    __in HDC hdc,
    __in PRECT ClientRect
    );

VOID PhTnpDrawPlusMinusGlyph(
    __in HDC hdc,
    __in PRECT Rect,
    __in BOOLEAN Plus
    );

// Tooltips

VOID PhTnpInitializeTooltips(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpGetTooltipText(
    __in PPH_TREENEW_CONTEXT Context,
    __in PPOINT Point,
    __out PWSTR *Text
    );

BOOLEAN PhTnpPrepareTooltipShow(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpPrepareTooltipPop(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpPopTooltip(
    __in PPH_TREENEW_CONTEXT Context
    );

// Double buffering

VOID PhTnpCreateBufferedContext(
    __in PPH_TREENEW_CONTEXT Context
    );

VOID PhTnpDestroyBufferedContext(
    __in PPH_TREENEW_CONTEXT Context
    );

// Support functions

VOID PhTnpGetMessagePos(
    __in HWND hwnd,
    __out PPOINT ClientPoint
    );

// Macros

#define TNP_HIT_TEST_FIXED_DIVIDER(X, Context) (Context->FixedColumn && (X) >= (Context)->FixedWidth - 8 && (X) < (Context)->FixedWidth + 8)
#define TNP_HIT_TEST_PLUS_MINUS_GLYPH(X, NodeLevel) (((X) >= 6 + ((LONG)(NodeLevel) * SmallIconWidth)) && ((X) < 6 + ((LONG)(NodeLevel) * SmallIconWidth) + SmallIconWidth))

#endif