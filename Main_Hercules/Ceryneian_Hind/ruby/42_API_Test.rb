require "oauth2"
UID = "1f117c968b63eab7dca2cc7d40b8291ec2f957dafea9a3bf68c4e021ffab92be"
SECRET = "01811c0418688145ed48d5cac69c4046efe7cd9f0dc61de713e53c3b60cc64ed"
# Create the client with your credentials
client = OAuth2::Client.new(UID, SECRET, site: "https://api.intra.42.fr")
# Get an access token
token = client.client_credentials.get_token

#token.get("/v2/cursus").parsed
# => [{"id"=>1, "created_at"=>"2014-11-02T17:43:38.480+01:00", "name"=>"42", "slug"=>"42", "users_count"=>1918, "users_url"=>"https://api.intra.42.fr/v2/cursus/42/users", "projects_url"=>"https://api.intra.42.fr/v2/cursus/42/projects", "topics_url"=>"https://api.intra.42.fr/v2/cursus/42/topics"}, ...]

#puts users_in_cursus = token.get("/v2/cursus/42/users").parsed
# => {"id"=>2, "login"=>"avisenti", "url"=>"https://api.intra.42.fr/v2/users/avisenti", "end_at"=>nil}, {"id"=>3, "login"=>"spariaud", "url"=>"https://api.intra.42.fr/v2/users/spariaud", "end_at"=>nil}, ...
#puts users_in_cursus.count
# => 30

#puts second_page = token.get("/v2/cursus/42/users", params: {page: {number: 2, size: 30}})
# => #<OAuth2::Response:0x007f9ba3b7eb98 @response=#<Faraday::Response:0x007f9ba3b949c0 @on_complete_callbacks=[], @env=#<Faraday::Env @method=:get @body="[{\"id\":35,\"login\":\"droger\",\"url\":\"https://api.intra.42.fr/v2/users/droger\",\"end_at\":null},{\"id\":36,\"login\":\"edelbe\",\"url\":\"https://api.intra.42.fr/v2/users/edelbe\"...
#puts second_page.parsed
# => {"id"=>35, "login"=>"droger", "url"=>"https://api.intra.42.fr/v2/users/droger", "end_at"=>nil}, {"id"=>36, "login"=>"edelbe", "url"=>"https://api.intra.42.fr/v2/users/edelbe", "end_at"=>nil}, ...

#second_page.headers["Link"]
# => "<https://api.intra.42.fr/v2/cursus/42/users?page=3>; rel=\"next\", <https://api.intra.42.fr/v2/cursus/42/users?page=1>; rel=\"prev\", <https://api.intra.42.fr/v2/cursus/42/users?page=1>; rel=\"first\", <https://api.intra.42.fr/v2/cursus/42/users?page=64>; rel=\"last\""

puts locations = token.get("/v2/users/jcasino/locations")

puts locations.parsed
