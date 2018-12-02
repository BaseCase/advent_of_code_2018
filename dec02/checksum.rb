puts "Starting part 1..."

twos = 0
threes = 0

File.read('./input.txt').split("\n").each do |line|
  counts = Hash.new { |h, k| h[k] = 0 }
  line.each_char { |c| counts[c] += 1 }
  if counts.values.include? 2 then twos += 1 end
  if counts.values.include? 3 then threes += 1 end
end

puts "Checksum is #{twos * threes}"


puts "Starting part 2..."
input = File.read('./input.txt').split("\n").map { |line| line.split('') }


def locate_distance_1_strings(input)
  (0..input.length - 1).each do |i|
    (i..input.length - 1).each do |candidate|
      diffs = 0
      input[i].each_with_index do |c, idx|
        if c != input[candidate][idx]
          diffs += 1
        end
      end
      if diffs == 1
        a = input[i]
        b = input[candidate]
        return [a, b]
      end
    end
  end
end

a, b = locate_distance_1_strings(input)
answer = a.select.with_index do |c, idx|
  b[idx] == c
end
puts answer.join
