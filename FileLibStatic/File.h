#pragma once
#include<iostream>
using namespace std;

template<class F>
class File
{
private:
    
    F* Queue;//pointeurs sur les elemnts de la Queue
    int nbelem;//nombre d element
    int fin;//fin de la Queue
    int debut;//debut de la Queue

public:
    File(int);
    ~File();
    void Enfiler(F);
    F Defiler();
    bool FileSaturee();
    bool FileVide() const;
    void ResizeFile();
    void Afficher() const;
};

template<class F>
inline File<F>::File(int capacite): nbelem(capacite),debut(0),fin(0)
{
    this->Queue = new F[this->nbelem];
}

template<class F>
inline File<F>::~File()
{
    delete[] Queue;
}

template<class F>
inline void File<F>::ResizeFile()
{
    int nouvelleCapacite = nbelem * 2;
    F* nouvelleQueue = new F[nouvelleCapacite];

    // Copier les éléments dans le nouvel espace
    int j = 0;
    for (int i = debut; i != fin; i++)
    {
        nouvelleQueue[j++] = Queue[i];
    }

    delete[] Queue;            // Libérer l'ancienne mémoire
    Queue = nouvelleQueue;     // Pointeur sur la nouvelle file
    nbelem = nouvelleCapacite; // Mettre à jour la capacité
    debut = 0;                 // Réinitialiser le début
    fin = j;                   // Mettre à jour la fin
}

template<class F>
inline bool File<F>::FileSaturee()
{
    if ((fin - debut + 1) == nbelem)
        throw std::runtime_error("Erreur : La file est plein (Overflow)");

    return false;
}

template<class F>
inline bool File<F>::FileVide() const
{
    if (debut == 0 && fin == 0)
        throw std::runtime_error("Erreur : La file est vide (Underflow)");
}


template<class F>
inline void File<F>::Enfiler(F elem)
{
    
        try
        {
            FileSaturee();
        }
        catch (const std::runtime_error& e)
        {
            ResizeFile(); // Redimensionner la file
        }

        this->Queue[fin] = elem;
        fin = (fin + 1) % nbelem; // Utilisation circulaire de l'indice fin
   
 
}


template<class F>
inline F File<F>::Defiler()
{
    try
    {
        FileVide();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl; // Affiche l'erreur
       
    }

    F x = this->Queue[this->debut];
    this->debut++;
    return x;
}





template<class F>
inline void File<F>::Afficher() const
{
    try
    {
        FileVide();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl; // Affiche l'erreur

    }
    std::cout << "Elements de la file : ";
    for (int i = debut; i != fin; i++)
    {
        std::cout << Queue[i] << " ";
    }
    std::cout << std::endl;
}

