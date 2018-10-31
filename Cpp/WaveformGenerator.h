
#pragma once

void GenerateSaw(
    unsigned int N,
    double phase,
    const double* f,
    double* y);

void GenerateSquare(
    unsigned int N,
    double phase,
    const double* f,
    const double* pw,
    double* y);