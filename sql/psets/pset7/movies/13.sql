SELECT DISTINCT name FROM
people JOIN stars on people.id = stars.person_id
JOIN movies on stars.movie_id = movies.id
WHERE movie_id in 
(
	SELECT movie_id FROM
	movies JOIN stars on movies.id = stars.movie_id
	JOIN people on stars.person_id = people.id
	WHERE name="Kevin Bacon" AND birth=1958
)
AND name!="Kevin Bacon";