SELECT title FROM 
movies JOIN stars on movies.id = stars.movie_id
JOIN people on stars.person_id = people.id
WHERE name="Johnny Depp" OR name="Helena Bonham Carter"
GROUP BY title
HAVING COUNT(*) > 1;