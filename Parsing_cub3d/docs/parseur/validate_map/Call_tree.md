                [ validate_map ]
                         |
           +-------------+-------------+
           |                           |
  [ check_border_line ]           [ scan_row ]
                                       |
                         +-------------+-------------+
                         |                           |
                 [ line_bounds_ok ]            [ handle_cell ]
                         |                           |
                  [ trimmed_len ]           +--------+--------+
                                            |                 |
                                   [ space_neighbors_ok ] [ zero_position_ok ]
                                            |                 |
                                     [ wall_span_ok ]   [ wall_span_ok ]
                                            |                 |
                                     [ trimmed_len ]   [ trimmed_len ]