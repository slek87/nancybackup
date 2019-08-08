
algoArr=("UCTS" "GUCT" "UCTS" "GUCTS" "UCTnancy" "GUCTnancy" "UCTSnancy" "GUCTSnancy" "UCTie" "GUCTie" "UCTSie" "GUCTSie" "WAS" "WASie" "WASnancy")

for algo in "${algoArr[@]}"
do
    ./plot_play.py Pancake ../../results $algo
    ./plot_play.py PancakeDPS ../../results $algo
    ./plot_play.py SlidingPuzzle ../../results $algo
    ./plot_play.py HeavyTile ../../results $algo
    ./plot_play.py TreeWorld ../../results $algo
done

