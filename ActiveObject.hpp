#ifndef ACTIVE_OBJECT_HPP
#define ACTIVE_OBJECT_HPP

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <atomic>

/**
 * @class ActiveObject
 * @brief Active Object qui exécute des tâches de manière asynchrone et transmet les résultats.
 */
class ActiveObject {
public:
    ActiveObject();
    ~ActiveObject();

    void start();
    void stop();
    void enqueue(std::function<std::string()> task);

    /**
     * @brief Définit l'étape suivante dans le pipeline.
     * @param next Un pointeur vers le prochain ActiveObject.
     */
    void setNextStage(ActiveObject* next);

private:
    std::queue<std::function<std::string()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    std::thread workerThread;
    std::atomic<bool> running;
    ActiveObject* nextStage = nullptr; ///< Étape suivante dans le pipeline.
};

#endif // ACTIVE_OBJECT_HPP