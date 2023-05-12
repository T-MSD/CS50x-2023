SELECT DISTINCT name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id
IN (SELECT movies.id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id WHERE people.name = 'Kevin Bacon' AND people.birth = 1958) AND NOT (people.name = 'Kevin Bacon' AND people.birth = 1958);
