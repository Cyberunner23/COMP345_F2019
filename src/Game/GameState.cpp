#include "GameState.hpp"

void GameState::NotifyObservers(int id)
{
	Notify(id);

}
void GameState::NotifyObservers()
{
    Notify();
}