SELECT name FROM people WHERE id in
(
	SELECT DISTINCT person_id FROM
	movies JOIN directors on movies.id = directors.movie_id
	JOIN ratings on movies.id = ratings.movie_id
	WHERE rating>=9.0
)