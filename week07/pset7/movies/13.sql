SELECT DISTINCT(p.name) AS name
  FROM people AS p,
       stars AS s,
       movies as m
 WHERE p.id = s.person_id
   AND m.id = s.movie_id
   AND NOT (p.name = "Kevin Bacon" AND p.birth = 1958)
   AND m.title IN
       (SELECT m.title AS title
          FROM movies AS m,
              stars AS s,
              people AS p
          WHERE (p.name = "Kevin Bacon" AND p.birth = 1958)
            AND p.id = s.person_id
            AND s.movie_id = m.id);