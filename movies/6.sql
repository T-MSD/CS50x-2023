SELECT AVG(rating) FROM ratings WHERE movie_id IN (SELECT id FROM movies WHERE year = 2012);
/* IN instead of = because the subquery returns more than one row */