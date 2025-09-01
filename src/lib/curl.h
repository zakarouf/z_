/**
    z_, Core Language Module with datatypes, memory tracker, and beyond.
    Copyright (C) 2025  Zakarouf

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ZAKAROUF_CURLWRAP_H
#define ZAKAROUF_CURLWRAP_H

typedef struct z__Curl z__Curl;
z__Curl *z__Curl_new(void);
void z__Curl_delete(z__Curl *zc);
void z__Curl_request(z__Curl *zc, const char *link_nullterm);

#ifdef Z__IMPLEMENTATION 
#include <stdlib.h>
#include <string.h>

#include <z_/arr.h>
#include <curl/curl.h>

struct z__Curl {
    CURL *handle;
    z__byteArr data;
    CURLcode code;
};

static size_t _WriteMemoryCallback(
    void *contents, size_t size
    , size_t nmemb, void *userp) 
{
    size_t realsize = size * nmemb;
    z__byteArr *mem = (z__byteArr *)userp;

    z__Arr_expand_ifneeded(mem, realsize+1);

    memcpy(&(mem->data[mem->lenUsed]), contents, realsize);
    mem->lenUsed += realsize;
    mem->data[mem->lenUsed] = 0;
    printf("hi %zu %zu\n", size, nmemb);
    return realsize;
}

z__Curl *z__Curl_new(void)
{
    z__Curl *zc = z__MALLOC(sizeof(*zc));
    zc->handle = curl_easy_init();
    z__Arr_new(&zc->data, 1024);
    return zc;
}

void z__Curl_delete(z__Curl *zc)
{
    z__Arr_delete(&zc->data);
    curl_easy_cleanup(zc->handle);
    z__FREE(zc);
}

void z__Curl_request(z__Curl *zc, const char *link_nullterm)
{
      CURL *curl_handle = zc->handle;
      zc->data.lenUsed = 0;
      curl_easy_setopt(curl_handle, CURLOPT_URL, link_nullterm);
      curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);
      curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, _WriteMemoryCallback);
      curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&zc->data);
      curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

      zc->code = curl_easy_perform(curl_handle);
}

#endif
#endif
