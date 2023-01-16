# include "Cub3d.h"

t_wall	cast (t_data *game, t_wall wall) {
	double xintercept, yintercept = {0};
	double xstep, ystep = {0};
	double isDown, isUp = 0;
	double isRight, isLeft = 0;

	int HorizHit = 0;
	double HoriwallHitx = 0;
	double HoriwallHity = 0;
	isDown = game->ray.ray_angle > 0 && game->ray.ray_angle < M_PI;
	isUp = !isDown;

	isRight = game->ray.ray_angle < M_PI / 2 || game->ray.ray_angle > 3 * (M_PI / 2);
	isLeft = !isRight;
	yintercept = floor((game->p.y / g_v.title_size)) * g_v.title_size;
	if (isDown)
		yintercept += g_v.title_size;
	xintercept = game->p.x + ((yintercept - game->p.y) / tan(game->ray.ray_angle));

	ystep = g_v.title_size;
		if (isUp)
			ystep *= -1;
	xstep = g_v.title_size / tan(game->ray.ray_angle);
	if (isLeft && xstep > 0)
		xstep *= -1;
	if (isRight && xstep < 0)
		xstep *= -1;
	double nextHorix = xintercept;
	double nextHoriy = yintercept;
	int flag = 0;
	if (isUp)
		flag = 1;

	while (nextHorix >= 0 && nextHorix < g_v.map_num_width
		&& nextHoriy >= 0 && nextHoriy < g_v.map_num_height) {
		if (isWall(game, nextHorix, nextHoriy - flag, 'n') == 1) {
			HorizHit = 1;
			HoriwallHitx = nextHorix;
			HoriwallHity = nextHoriy;
			break ;

		}
		else if (isWall(game, nextHorix, nextHoriy - flag, 'n') == 0) {
			nextHorix += xstep;
			nextHoriy += ystep;
		}
		else
			break ;
	}
	flag = 0;

	// vertical
	int VertHit = 0;
	double vertiwallHitx = 0;
	double vertiwallHity = 0;

	xintercept = floor((game->p.x / g_v.title_size)) * g_v.title_size;
	if (isRight)
		xintercept += g_v.title_size;
	yintercept = game->p.y + ((xintercept - game->p.x) * tan(game->ray.ray_angle));

	xstep = g_v.title_size;
		if (isLeft)
			xstep *= -1;
	ystep = g_v.title_size * tan(game->ray.ray_angle);
	if (isUp && ystep > 0)
		ystep *= -1;
	if (isDown && ystep < 0)
		ystep *= -1;

	double	nextvertix = xintercept;
	double nextvertiy = yintercept;
	if (isLeft)
		flag = 1;

	while (nextvertix >= 0 && nextvertix < g_v.map_num_width
		&& nextvertiy >= 0 && nextvertiy < g_v.map_num_height) {
		if (isWall(game, nextvertix - flag, nextvertiy, 'n') == 1) {
			VertHit = 1;
			vertiwallHitx = nextvertix;
			vertiwallHity = nextvertiy;
			break ;
		}
		else if (isWall(game, nextvertix - flag, nextvertiy, 'n') == 0) {
			nextvertix += xstep;
			nextvertiy += ystep;
		}
		else
			break ;
	}

	// caluculate both distances
	double horzHitDistance = -1;
	double vertHitDistance = -1;
	double distance;
	if (HorizHit == 1)
		horzHitDistance = distanceBetweenPointx(game->p.x, game->p.y, HoriwallHitx, HoriwallHity);
	if (VertHit == 1)
		vertHitDistance = distanceBetweenPointx(game->p.x, game->p.y, vertiwallHitx, vertiwallHity);

	distance = get_distance (horzHitDistance, vertHitDistance);
	if (distance == vertHitDistance)
		wall.is_vertical = true;
	else
		wall.is_horisantal = true;
	wall.rays = distance;
	return (wall);
	// render_line(game, wall.rays, game->ray.ray_angle);
}

t_wall*	raycasting (t_data *game) {
	int i = 0;
	int columId = 0;
	t_wall *wall;
	game->ray.ray_angle = game->p.direction - (game->ray.fov_angle / 2);
	wall = (t_wall*)malloc(sizeof(t_wall) * game->ray.num_rays);
	while (i < game->ray.num_rays) {
		if (game->ray.ray_angle < 0)
			game->ray.ray_angle += M_PI * 2;
		else if (game->ray.ray_angle > M_PI * 2)
			game->ray.ray_angle -= M_PI * 2;
		wall[columId] = cast(game, wall[i]);
		game->ray.ray_angle += game->ray.fov_angle / game->ray.num_rays;
		i++;
		columId++;
	}
	return (wall);
}