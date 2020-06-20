SELECT name FROM people WHERE id in
(
	SELECT DISTINCT person_id FROM
	movies JOIN stars on movies.id = stars.movie_id
	JOIN people on stars.person_id = people.id
	WHERE year=2004
)
ORDER BY birth;