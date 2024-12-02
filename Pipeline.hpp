#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include "ActiveObject.hpp"
#include <vector>
#include <functional>
#include <memory>
#include <string>

/**
 * @class Pipeline
 * @brief Représente un pipeline composé d'ActiveObjects, créé automatiquement pour les tâches fournies.
 */
class Pipeline {
public:
    Pipeline();
    ~Pipeline();

    /**
     * @brief Ajoute une tâche au pipeline.
     * @param task Une fonction qui renvoie un std::string.
     */
    void addTask(std::function<std::string()> task);

    /**
     * @brief Démarre toutes les étapes du pipeline.
     */
    void start();

    /**
     * @brief Exécute le pipeline en transmettant un std::string partagé entre les étapes.
     * @param sharedData La chaîne partagée entre les étapes.
     */
    std::string execute();

    /**
     * @brief Arrête toutes les étapes du pipeline.
     */
    void stop();

private:
    std::vector<std::shared_ptr<ActiveObject>> stages; ///< Étapes du pipeline.
};

#endif // PIPELINE_HPP