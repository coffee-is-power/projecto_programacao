#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "weatherapi.h"
#include <jansson.h>
const char* weather_code_table[311];
int main(int argc, char *argv[]) {
    weather_code_table[113] = "Sol ☀️";
    weather_code_table[116] = "Um pouco nublado ⛅";
    weather_code_table[119] = "Nublado ☁️☁️☁️☁️☁️";
    weather_code_table[122] = "Encoberto ☁️";
    weather_code_table[143] = "Misto ⛆☀️";
    weather_code_table[176] = "Possibilidade de chuva ⛆";
    weather_code_table[179] = "Possibilidade de neve 🌨️";
    weather_code_table[182] = "Possibilidade de neve molhada irregular";
    weather_code_table[185] = "Possibilidade de chuvisco gelado irregular";
    weather_code_table[200] = "Possibilidade de trovoada ⛈️";
    weather_code_table[248] = "Nevoeiro ☁️☁️";
    weather_code_table[263] = "Chuvisco ⛆";
    weather_code_table[266] = "Chuvisco leve ⛆";
    weather_code_table[281] = "Chuvisco gelado ⛆";
    weather_code_table[284] = "Chuvisco gelado  leve ⛆";
    weather_code_table[293] = "Chuva fraca irregular ⛆";
    weather_code_table[296] = "Chuva leve ⛆";
    weather_code_table[299] = "Chuva moderada ás vezes ⛆☀️⛆☀️⛆";
    weather_code_table[302] = "Chuva moderada ⛆⛆";
    weather_code_table[305] = "Chuva pesada ás vezes ⛆⛆⛆⛆☀️⛆⛆⛆⛆☀️⛆⛆⛆⛆☀️";
    weather_code_table[308] = "Chuva pesada ⛆⛆⛆⛆";
    weather_code_table[311] = "Chuva fraca e gelada ⛆";

    if (argc != 2) {
        fprintf(stderr, "Como usar: %s <LOCALIDADE>\n\n", argv[0]);
        fprintf(stderr, "Mostra o tempo de uma localidade\n\n");
        return 2;
    }
    WeatherApiResponse weather;
    json_t* weather_json_root = fetch_weather(argv[1], &weather);
    if(!weather_json_root) {
        printf("Ocorreu um erro de conexão");
    }
    printf("Temperatura sentida: %.2f Cº\n", weather.current.feelslike);
    printf("Temperatura: %.2f Cº\n", weather.current.temperature);
    printf("Tempo: %s\n", weather_code_table[weather.current.weather_code]);
    json_decref(weather_json_root);
    return 0;
}
