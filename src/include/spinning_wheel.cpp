
wchar_t spin_clockwise(wchar_t c) {
    switch(c) {
        case '\\': return '|';

        case '|': return '/';

        case '/': return L'—';

        case L'—': return '\\';

        default: return c;
    }
}

wchar_t spin_counterclockwise(wchar_t c) {
    switch(c) {
        case '\\': return L'—';

        case '|': return '\\';

        case '/': return '|';

        case L'—': return '/';

        default: return c;
    }
}