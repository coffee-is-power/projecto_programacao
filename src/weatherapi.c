#include "weatherapi.h"
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <jansson.h>

#define BUFFER_SIZE (1024 * 1024) /* 1MB */

#define ACCESS_TOKEN "e35dcd6f74b233e400cd2f8a1139a1ec"
#define URL_FORMAT "http://api.weatherstack.com/current?access_key=" ACCESS_TOKEN "&query=%s"
#define URL_SIZE BUFFER_SIZE

/* Return the offset of the first newline in text or the length of
   text if there's no newline */
static int newline_offset(const char *text)
{
    const char *newline = strchr(text, '\n');
    if (!newline)
        return strlen(text);
    else
        return (int)(newline - text);
}

struct write_result
{
    char *data;
    int pos;
};

static size_t write_response(void *ptr, size_t size, size_t nmemb, void *stream)
{
    struct write_result *result = (struct write_result *)stream;

    if (result->pos + size * nmemb >= BUFFER_SIZE - 1)
    {
        fprintf(stderr, "error: too small buffer\n");
        return 0;
    }

    memcpy(result->data + result->pos, ptr, size * nmemb);
    result->pos += size * nmemb;

    return size * nmemb;
}

static char *request(const char *url)
{
    CURL *curl = NULL;
    CURLcode status;
    struct curl_slist *headers = NULL;
    char *data = NULL;
    long code;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (!curl)
        goto error;

    data = malloc(BUFFER_SIZE);
    if (!data)
        goto error;

    struct write_result write_result = {.data = data, .pos = 0};

    curl_easy_setopt(curl, CURLOPT_URL, url);

    /* GitHub commits API v3 requires a User-Agent header */
    headers = curl_slist_append(headers, "User-Agent: Jansson-Tutorial");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &write_result);

    status = curl_easy_perform(curl);
    if (status != 0)
    {
        fprintf(stderr, "error: unable to request data from %s:\n", url);
        fprintf(stderr, "%s\n", curl_easy_strerror(status));
        goto error;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
    if (code != 200)
    {
        fprintf(stderr, "error: server responded with code %ld\n", code);
        goto error;
    }

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    /* zero-terminate the result */
    data[write_result.pos] = '\0';

    return data;

error:
    if (data)
        free(data);
    if (curl)
        curl_easy_cleanup(curl);
    if (headers)
        curl_slist_free_all(headers);
    curl_global_cleanup();
    return NULL;
}

json_t* fetch_weather(const char* location, WeatherApiResponse *result)
{
    size_t i;
    char *text;
    char url[URL_SIZE];
    snprintf(url, URL_SIZE, URL_FORMAT, location);
    json_t *root;
    json_error_t error;
    text = request(url);
    if (!text)
        return NULL;
    root = json_loads(text, 0, &error);
    free(text);
    if (!root)
        return NULL;
    json_t* current = json_object_get(root, "current");
    json_t* json_location = json_object_get(root, "location");
    json_t* request = json_object_get(root, "request");
    json_t
        *request_type = json_object_get(request, "type"),
        *request_query = json_object_get(request, "query"),
        *request_language = json_object_get(request, "language"),
        *request_unit = json_object_get(request, "unit");
    json_t
        *location_name = json_object_get(json_location, "name"),
        *location_country = json_object_get(json_location, "country"),
        *location_lat = json_object_get(json_location, "lat"), 
        *location_lon = json_object_get(json_location, "lon"),
        *location_timezone_id = json_object_get(json_location, "timezone_id"),
        *location_localtime_epoch = json_object_get(json_location, "localtime_epoch"),
        *location_region = json_object_get(json_location, "region"),
        *location_localtime = json_object_get(json_location, "localtime"),
        *location_utc_offset = json_object_get(json_location, "utc_offset");

    json_t
        *observation_time = json_object_get(current, "observation_time"),
        *temperature = json_object_get(current, "temperature"),
        *weather_code = json_object_get(current, "weather_code"),
        *wind_speed = json_object_get(current, "wind_speed"),
        *wind_degree = json_object_get(current, "wind_degree"),
        *wind_dir = json_object_get(current, "wind_dir"),
        *pressure = json_object_get(current, "pressure"),
        *precip = json_object_get(current, "precip"),
        *humidity = json_object_get(current, "humidity"),
        *cloudcover = json_object_get(current, "cloudcover"),
        *feelslike = json_object_get(current, "feelslike"),
        *uv_index = json_object_get(current, "uv_index"),
        *visibility= json_object_get(current, "visibility");
    *result = (WeatherApiResponse) {
        .request = (WeatherApiRequestInfo) {
            .type = json_string_value(request_type),
            .query = json_string_value(request_query),
            .unit = json_string_value(request_unit),
            .language = json_string_value(request_language)
        },
        .current = (Weather) {
            .observation_time = json_string_value(observation_time),
            .temperature = json_number_value(temperature),
            .weather_code = json_number_value(weather_code),
            .wind_speed = json_number_value(wind_speed),
            .wind_degree = json_number_value(wind_degree),
            .wind_dir = json_string_value(wind_dir),
            .pressure = json_number_value(pressure),
            .precip = json_number_value(precip),
            .humidity = json_number_value(humidity),
            .cloudcover = json_number_value(cloudcover),
            .feelslike = json_number_value(feelslike),
            .uv_index = json_number_value(uv_index),
            .visibility = json_number_value(visibility)
        },
        .location = (Location) {
            .name = json_string_value(location_name),
            .country = json_string_value(location_country),
            .region = json_string_value(location_region),
            .lat = strtod(json_string_value(location_lat), NULL),
            .lon = strtod(json_string_value(location_lon), NULL),
            .timezone_id = json_string_value(location_timezone_id),
            .localtime = json_string_value(location_localtime),
            .localtime_epoch = json_number_value(location_localtime_epoch),
            .utc_offset = strtod(json_string_value(location_utc_offset), NULL),
        }
    };
    return root;
}