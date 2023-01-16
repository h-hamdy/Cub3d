# include "Cub3d.h"

double	distanceBetweenPointx (double x1, double y1, double x2, double y2) {
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double get_distance (double horzHitDistance, double vertHitDistance) {
	if (horzHitDistance == -1)
			return (vertHitDistance);
	else if (vertHitDistance == -1)
			return (horzHitDistance);
	if (horzHitDistance < vertHitDistance)
		return (horzHitDistance);
	return (vertHitDistance);
}