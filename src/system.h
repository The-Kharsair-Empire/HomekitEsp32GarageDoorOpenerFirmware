#pragma once

#ifndef SYSTEM_H
#define SYSTEM_H
#include <Arduino.h>


#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif



#endif
