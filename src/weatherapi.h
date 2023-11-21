#include <stdbool.h>
#include <jansson.h>

typedef struct
{
    const char* type;
    const char* query;
    const char* language;
    const char* unit;
} WeatherApiRequestInfo;
typedef struct
{
    const char* name;
    const char* country;
    const char* region;
    double lat;
    double lon;
    const char* timezone_id;
    const char* localtime;
    unsigned long localtime_epoch;
    double utc_offset;
} Location;
typedef struct
{

    const char*               observation_time;
    double            temperature;
    unsigned int      weather_code;
    // const char* *             weather_icons;
    // long unsigned int weather_icons_len;
    // const char* *             weather_descriptions;
    // long unsigned int weather_descriptions_len;
    double            wind_speed;
    double            wind_degree;
    const char*               wind_dir;
    double            pressure;
    double            precip;
    double            humidity;
    double            cloudcover;
    double            feelslike;
    double            uv_index;
    double            visibility;
} Weather;
typedef struct
{
    WeatherApiRequestInfo request;
    Location location;
    Weather current;
} WeatherApiResponse;

json_t* fetch_weather(const char* location, WeatherApiResponse* result);