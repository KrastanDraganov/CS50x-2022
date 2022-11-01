SELECT COUNT(*) AS perfect_rating_count
  FROM movies
 WHERE id IN
       (SELECT movie_id
          FROM ratings
         WHERE rating = 10.0);