  SELECT m.title AS title
    FROM movies AS m,
         stars AS s,
         people AS p,
         ratings AS r
   WHERE p.name = "Chadwick Boseman"
     AND p.id = s.person_id
     AND s.movie_id = m.id
     AND r.movie_id = m.id
ORDER BY r.rating DESC
   LIMIT 5;