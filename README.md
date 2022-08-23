# HighlightTextPainterSample
This sample shows a class, called HighlightTextPainter, that has the ability to draw given text with highlight tokens (keywords). It automatically breaks the text into multiple lines when needed.

Usage:
```c++
    case WM_PAINT:
        {
            HighlightTextPainter::DefaultSplitter splitter(false);
            HighlightTextPainter text(&splitter, L"This sample shows a class, called HighlightTextPainter, that has the ability to draw given text with highlight tokens (keywords). It automatically breaks the text into multiple lines when needed.\n\nPlease try resizing this window."
                , L"keyword this that class");

            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
            // TODO: Setup text font here

            RECT rc;
            GetClientRect(hWnd, &rc);
            HighlightTextPainter::GDIPainter painter(hdc);
            text.Draw(&painter, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, false);

            EndPaint(hWnd, &ps);
        }
        break;

```

![screenshot](https://github.com/huxia1124/HighlightTextPainterSample/blob/master/HighlightTextPainter.png)
