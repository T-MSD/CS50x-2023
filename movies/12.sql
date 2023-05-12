SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id WHERE name IN ('Johnny Depp', 'Helena Bonham Carter')
GROUP BY movies.title HAVING COUNT(*) = 2;
/* name IN ('Johnny Depp', 'Helena Bonham Carter') returns movies with only one of them and both so we need count = 2 */