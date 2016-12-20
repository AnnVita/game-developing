#pragma once

void ProcessAnimation(SShapes & shapes);

void SyncRotateShapes(SShapes & shapes);
void AsyncRotateShapes(SShapes & shapes);
bool MoveByLine(SShapes & shapes, sf::Vector2f moveCoordinates, sf::Vector2f stopCoordinates);
bool ChangeSize(SShapes & shapes, sf::Vector2f increase, sf::Vector2f stopSize);
bool ChangeOpacity(SShapes & shapes, int changeSpeed, int stopOpacity);
bool ChangeCoordinatesByY(SShapes & shapes);
bool ChangeCoordinatesByX(SShapes & shapes);
bool ConfigurateLadder(SShapes & shapes);
bool ToSinglePosition(SShapes & shapes);
bool ConfigurateInline(SShapes & shapes);
