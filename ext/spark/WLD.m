function H_final = WLD(img, C, T, M)

[d1, d2] = size(img);

M1 = [1, 1, 1; 1, -8, 1; 1, 1, 1];
img1 = conv2(double(img), double(M1));
M2 = [0, 0, 0; 0, 1, 0; 0, 0, 0];
img2 = conv2(double(img), double(M2));

img3 = atan(img1./img2);

edges_excitation = linspace(-pi/2, pi/2, C + 1);
edges_excitation(end) = edges_excitation(end) + 1e-3;
[~, feat_excitation] = histc(reshape(img3, [1, (d1+2)*(d2+2)]), edges_excitation);

M1 = [0, -1, 0; 0, 0, 0; 0, 1, 0];
img1 = conv2(double(img), double(M1));
M2 = [0, 0, 0; 1, 0, -1; 0, 0, 0];
img2 = conv2(double(img), double(M2));

img3 = atan2(img1, img2);
edges_angles = linspace(-pi, pi, T + 1);
edges_angles(end) = edges_angles(end) + 1e-3;
[~, feat_angles] = histc(reshape(img3, [1, (d1+2)*(d2+2)]), edges_angles);

bins = (feat_angles-1)*C + feat_excitation;
feat_ = zeros(1, C*T);
for i = 1:((d1+2)*(d2+2))
    feat_(bins(i)) = feat_(bins(i)) + 1;
end
feat_ = feat_/((d1+2)*(d2+2));

hist_ = reshape(feat_, [C, T]);

% form 1D histogram
H_final = zeros(1, C*T);
ind = 1;
for c = 1:(C/M)
    for t = 1:T
        ind_temp = (c-1)*M + 1;
        H_final(ind:(ind+M-1)) = hist_(ind_temp:(ind_temp+M-1), t);
        ind = ind + M;
    end
end
