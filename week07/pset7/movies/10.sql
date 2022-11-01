SELECT DISTINCT(p.name) AS name
  FROM people AS p,
       directors AS d,
       ratings AS r,
       movies AS m
 WHERE p.id = d.person_id
   AND d.movie_id = m.id
   AND r.movie_id = m.id
   AND r.rating >= 9.0;