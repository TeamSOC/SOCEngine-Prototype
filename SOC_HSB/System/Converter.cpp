#include "../pch/pch.h"

std::wstring mbs_to_wcs(std::string const& str, std::locale const& loc)
{
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
	codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
	std::mbstate_t state = std::mbstate_t();
	std::vector<wchar_t> buf(str.size() + 1);
	char const* in_next = str.c_str();
	wchar_t* out_next = &buf[0];
	std::codecvt_base::result r = codecvt.in(state, 
		str.c_str(), str.c_str() + str.size(), in_next, 
		&buf[0], &buf[0] + buf.size(), out_next);
	if (r == std::codecvt_base::error)
		throw std::runtime_error("can't convert string to wstring");   
	return std::wstring(&buf[0]);
}

std::string wcs_to_mbs(std::wstring const& str, std::locale const& loc)
{
    typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
    codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
    std::mbstate_t state = std::mbstate_t();
    std::vector<char> buf((str.size() + 1) * codecvt.max_length());
    wchar_t const* in_next = str.c_str();
    char* out_next = &buf[0];
    std::codecvt_base::result r = codecvt.out(state, 
        str.c_str(), str.c_str() + str.size(), in_next, 
        &buf[0], &buf[0] + buf.size(), out_next);
    if (r == std::codecvt_base::error)
       throw std::runtime_error("can't convert wstring to string");   
    return std::string(&buf[0]);
}

#if defined(_WIN32) || defined(_WIN64)
void UnicodeFromMB(const char *mb, wchar_t *uni)
{
	int len = static_cast<int>(strlen(mb));

	MultiByteToWideChar(CP_ACP, 0, mb, len, uni, len);

	uni[len] = L'\0';
}
#endif