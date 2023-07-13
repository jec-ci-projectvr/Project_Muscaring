// Fill out your copyright notice in the Description page of Project Settings.


#include "InterfaceGhostState.h"

// Add default functionality here for any IInterfaceGhostState functions that are not pure virtual.
ANormalGhost::GhostState IInterfaceGhostState::SendGhostState(ANormalGhost::GhostState state)
{
	return state;
}
ARestArea& IInterfaceGhostState::SendMostNearRestArea(TObjectPtr<ARestArea> restArea)
{
     return *restArea;
}
bool IInterfaceGhostState::SendHitInfo(bool hit)
{
	return hit;
}