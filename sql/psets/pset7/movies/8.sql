SELECT name FROM
movies JOIN stars on movies.id = stars.movie_id
JOIN people on stars.person_id = people.id
WHERE title="Toy Story";