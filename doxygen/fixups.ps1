$f='.\cppx-core DOxygen-generated documentation\docs\search\search.js'
$original='searchBox.OnSelectItem(0);'
$fixed=$original + ' toggleLevel(4);'
(get-content -path $f -raw).Replace( $original, $fixed ) | set-content -path $f
