#pragma once

std::wstring mbs_to_wcs(std::string const& str, std::locale const& loc = std::locale());
std::string wcs_to_mbs(std::wstring const& str, std::locale const& loc = std::locale());


#if defined(_WIN32) || defined(_WIN64)
void UnicodeFromMB(const char *mb, wchar_t *uni);
#endif