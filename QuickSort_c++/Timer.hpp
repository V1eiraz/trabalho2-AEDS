#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>


// Mede o tempo de execução de trechos de código com alta precisão,
// utilizando std::chrono (disponível desde C++11).

class Timer {
public:

    void start() {
        begin_ = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_ = std::chrono::high_resolution_clock::now();
    }

    // Retorna o tempo decorrido em milissegundos (double para precisão decimal)
    double elapsedMilliseconds() const {
        return std::chrono::duration<double, std::milli>(end_ - begin_).count();
    }

    // Retorna o tempo decorrido em segundos
    double elapsedSeconds() const {
        return std::chrono::duration<double>(end_ - begin_).count();
    }

private:
    // high_resolution_clock é o relógio de maior resolução disponível
    // no sistema — ideal para benchmarks de algoritmos.
    std::chrono::time_point<std::chrono::high_resolution_clock> begin_;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_;
};

#endif